#include <map>
#include <utility>

#include "domain.hh"

namespace pddl_parser {

Domain::Domain(std::string &&name,
               std::deque<std::string> &&requirements,
               std::deque<TypedName> &&types,
               std::deque<TypedName> &&constants,
               std::deque<Predicate> &&predicates,
               std::deque<Function> &&functions,
               std::deque<Action> &&actions)
    : name(std::move(name)),
      requirements(std::move(requirements)) {
    for (TypedName &type : types) {
        std::string key(type.get_name());
        this->types[key] = std::move(type);
    }
    for (TypedName &constant : constants) {
        std::string key(constant.get_name());
        this->constants[key] = std::move(constant);
    }
    for (Predicate &predicate : predicates) {
        std::string key(predicate.get_name());
        this->predicates[key] = std::move(predicate);
    }
    for (Function &function : functions) {
        std::string key(function.get_name());
        this->functions[key] = std::move(function);
    }
    for (Action &action : actions) {
        std::string key(action.get_name());
        this->actions[key] = std::move(action);
    }
}

Domain::Domain(std::string &&name)
    : name(std::move(name)) {
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

void Domain::set_requirements(std::deque<std::string> &&requirements) {
    this->requirements = std::move(requirements);
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

std::ostream& operator<<(std::ostream &stream, Domain const &domain) {
    stream << "( define ( domain " << domain.name << " )" << std::endl;

    if (!domain.requirements.empty()) {
        stream << "  ( :requirements ";
        for (auto const &r : domain.requirements) {
            stream << r << " ";
        }
        stream << ")" << std::endl;
    }

    stream << "  ( :types";
    std::map<std::string,TypedName> ordered_types(domain.types.begin(),
                                                  domain.types.end());
    for (auto const &t : ordered_types) {
        stream << std::endl << "    " << t.second;
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
