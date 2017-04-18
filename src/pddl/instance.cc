#include <map>
#include <utility>

#include "instance.hh"

namespace pddl_parser {

Instance::Instance(std::string &&name,
                   Domain &domain,
                   std::deque<std::string> &&requirements,
                   std::unordered_map<std::string,TypedName> &&objects,
                   State &&init,
                   Condition &&goal)
    : name(std::move(name)),
      domain(domain),
      requirements(std::move(requirements)),
      objects(std::move(objects)),
      init(std::move(init)),
      goal(std::move(goal)) {
}

Instance::Instance(std::string &&name,
                   Domain &domain,
                   std::deque<std::string> &&requirements,
                   std::deque<TypedName> &&objects,
                   State &&init,
                   Condition &&goal)
    : name(std::move(name)),
      domain(domain),
      requirements(std::move(requirements)),
      init(std::move(init)),
      goal(std::move(goal)) {
    for (TypedName &object : objects) {
        std::string key(object.get_name());
        this->objects[key] = std::move(object);
    }
}

Instance::Instance(std::string &&name, Domain &domain)
    : name(std::move(name)),
      domain(domain) {
}

void Instance::set_requirements(std::deque<std::string> &&requirements) {
    this->requirements = std::move(requirements);
}

void Instance::set_objects(std::deque<TypedName> &&objects) {
    for (TypedName &object : objects) {
        std::string key(object.get_name());
        this->objects[key] = std::move(object);
    }
}

void Instance::add_init_predicate(std::string &name,
                                  std::deque<std::string> &parameters) {
    init.add_predicate(ground_predicate(name, parameters));
}

void Instance::add_init_function(std::string &name,
                                 std::deque<std::string> &parameters,
                                 double value) {
    init.add_function(ground_function(name, parameters, value));
}

void Instance::set_goal(Condition &&goal) {
    this->goal = std::move(goal);
}

Predicate const& Instance::get_predicate(std::string &name) const {
    return domain.get_predicate(name);
}

Function const& Instance::get_function(std::string &name) const {
    return domain.get_function(name);
}

TypedName const& Instance::get_object(std::string &name) const {
    auto object = objects.find(name);
    if (object != objects.end()) {
        return object->second;
    }
    else {
        return domain.get_constant(name);
    }
}

GroundPredicate Instance::ground_predicate(
    std::string &name,
    std::deque<std::string> &parameters) const {
    std::deque<std::reference_wrapper<TypedName const>> parameters_by_ref;
    for (auto &p : parameters) {
        parameters_by_ref.emplace_back(get_object(p));
    }
    return GroundPredicate(get_predicate(name),
                           std::move(parameters_by_ref));
}

GroundFunction Instance::ground_function(
    std::string &name,
    std::deque<std::string> &parameters,
    double value) const {
    std::deque<std::reference_wrapper<TypedName const>> parameters_by_ref;
    for (auto &p : parameters) {
        parameters_by_ref.emplace_back(get_object(p));
    }
    return GroundFunction(get_function(name),
                          std::move(parameters_by_ref),
                          value);
}

std::ostream& operator<<(std::ostream &stream, Instance const &instance) {
    stream << "( define ( problem " << instance.name << " )" << std::endl;

    stream << "  ( :domain " << instance.domain.get_name() << " )" << std::endl;

    if (!instance.requirements.empty()) {
        stream << "  ( :requirements ";
        for (auto const &r : instance.requirements) {
            stream << r << " ";
        }
        stream << ")" << std::endl;
    }

    stream << "  ( :objects";
    std::map<std::string,TypedName> ordered_objects(instance.objects.begin(),
                                                    instance.objects.end());
    for (auto const &o : ordered_objects) {
        stream << std::endl << "    " << o.second;
    }
    stream << " )" << std::endl;

    stream << "  ( :init";
    stream << instance.init << " )" << std::endl;

    stream << "  ( :goal " << instance.goal << " )" << std::endl;

    stream << " )" << std::endl;

    return stream;
}

} // namespace pddl_parser
