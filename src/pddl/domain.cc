#include <iterator>
#include <map>
#include <set>
#include <utility>

#include "domain.hh"

namespace pddl_parser {

Domain::Domain() {
    types["object"] = TypedName("object");
}

Domain::Domain(std::string &&name,
               std::deque<std::string> &&requirements,
               std::deque<TypedName> &&types,
               std::deque<TypedName> &&constants,
               std::deque<Predicate> &&predicates,
               std::deque<Function> &&functions,
               std::deque<Action> &&actions)
    : name(std::move(name)),
      requirements(std::make_move_iterator(requirements.begin()),
                   std::make_move_iterator(requirements.end())) {
    requirements.clear();
    for (TypedName &type : types) {
        std::string key(type.get_name());
        this->types[key] = std::move(type);
    }
    types.clear();
    for (TypedName &constant : constants) {
        std::string key(constant.get_name());
        this->constants[key] = std::move(constant);
    }
    constants.clear();
    for (Predicate &predicate : predicates) {
        std::string key(predicate.get_name());
        this->predicates[key] = std::move(predicate);
    }
    predicates.clear();
    for (Function &function : functions) {
        std::string key(function.get_name());
        this->functions[key] = std::move(function);
    }
    functions.clear();
    for (Action &action : actions) {
        std::string key(action.get_name());
        this->actions[key] = std::move(action);
    }
    actions.clear();
}

Predicate const& Domain::get_predicate(std::string &name) const {
    return predicates.at(name);
}

Function const& Domain::get_function(std::string &name) const {
    return functions.at(name);
}

TypedName const& Domain::get_constant(std::string &name) const {
    return constants.at(name);
}

void Domain::set_name(std::string &&name) {
    this->name = std::move(name);
}

void Domain::set_requirements(std::deque<std::string> &&requirements) {
    this->requirements = std::unordered_set<std::string>(
        std::make_move_iterator(requirements.begin()),
        std::make_move_iterator(requirements.end()));
}

void Domain::set_types(std::deque<TypedName> &&types) {
    for (TypedName &type : types) {
        std::string key(type.get_name());
        this->types[key] = std::move(type);
    }
}

void Domain::set_constants(std::deque<TypedName> &&constants) {
    for (TypedName &constant : constants) {
        std::string key(constant.get_name());
        this->constants[key] = std::move(constant);
    }
}

void Domain::set_predicates(std::deque<Predicate> &&predicates) {
    for (Predicate &predicate : predicates) {
        std::string key(predicate.get_name());
        this->predicates[key] = std::move(predicate);
    }
}

void Domain::set_functions(std::deque<Function> &&functions) {
    for (Function &function : functions) {
        std::string key(function.get_name());
        this->functions[key] = std::move(function);
    }
}

void Domain::add_action( pddl_parser::Action &&action ) {
    std::string key(action.get_name());
    this->actions[key] = std::move(action);
}

bool Domain::validate() const {
    bool valid = true;

    if (types.size() > 1 && !requirements.count(":typing")) {
        std::cerr << "ERROR: "
                  << "Using types but no \":typing\" in requirements."
                  << std::endl;
        valid = false;
    }

    if (!functions.empty() && !requirements.count(":fluents")) {
        std::cerr << "ERROR: "
                  << "Using functions but no \":fluents\" in requirements."
                  << std::endl;
        valid = false;
    }

    for (auto const &pair : predicates) {
        valid = pair.second.validate(types) && valid;
    }

    for (auto const &pair : functions) {
        valid = pair.second.validate(types) && valid;
    }

    for (auto const &pair : actions) {
        valid = pair.second.validate(types, constants) && valid;
    }

    return valid;
}

std::string const & Domain::get_name() const {
    return name;
}

std::unordered_map<std::string,Predicate> const & Domain::get_predicates() const {
    return predicates;
}

std::unordered_map<std::string,Function> const & Domain::get_functions() const {
    return functions;
}

std::unordered_map<std::string,Action> const & Domain::get_actions() const {
    return actions;
}

std::ostream& operator<<(std::ostream &stream, Domain const &domain) {
    stream << "( define ( domain " << domain.name << " )" << std::endl;

    if (!domain.requirements.empty()) {
        stream << "  ( :requirements ";
        std::set<std::string> ordered_requirements(
            domain.requirements.begin(),
            domain.requirements.end());
        for (auto const &r : ordered_requirements) {
            stream << r << " ";
        }
        stream << ")" << std::endl;
    }

    stream << "  ( :types";
    std::map<std::string,TypedName> ordered_types(domain.types.begin(),
                                                  domain.types.end());
    for (auto const &t : ordered_types) {
        if (t.second.get_name() != "object") {
            stream << std::endl << "    " << t.second;
        }
    }
    stream << " )" << std::endl;

    stream << "  ( :constants";
    std::map<std::string,TypedName> ordered_constants(domain.constants.begin(),
                                                      domain.constants.end());
    for (auto const &c : ordered_constants) {
        stream << std::endl << "    " << c.second;
    }
    stream << " )" << std::endl;

    stream << "  ( :predicates";
    std::map<std::string,Predicate> ordered_predicates(
        domain.predicates.begin(), domain.predicates.end());
    for (auto const &p : ordered_predicates) {
        stream << std::endl << "    " << p.second;
    }
    stream << " )" << std::endl;

    stream << "  ( :functions";
    std::map<std::string,Function> ordered_functions(domain.functions.begin(),
                                                     domain.functions.end());
    for (auto const &f : ordered_functions) {
        stream << std::endl << "    " << f.second;
    }
    stream << " )";

    std::map<std::string,Action> ordered_actions(domain.actions.begin(),
                                                 domain.actions.end());
    for (auto const &a : ordered_actions) {
        stream << std::endl << a.second;
    }

    stream << std::endl << " )" << std::endl;
    return stream;
}

} // namespace pddl_parser
