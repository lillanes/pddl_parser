#include <map>
#include <utility>

#include "instance.hh"

namespace pddl_parser {

void Instance::set_name(std::string &&name) {
    this->name = std::move(name);
}

void Instance::set_domain_name(std::string &&domain_name) {
    this->domain_name = std::move(domain_name);
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

void Instance::add_init_predicate(std::string &&name,
                                  std::deque<std::string> &&parameters) {
    init.add_predicate(std::move(name), std::move(parameters));
}

void Instance::add_init_function(std::string &&name,
                                 std::deque<std::string> &&parameters,
                                 double value) {
    init.add_function(std::move(name), std::move(parameters), value);
}

void Instance::set_goal(Condition &&goal) {
    this->goal = std::move(goal);
}

std::ostream& operator<<(std::ostream &stream, Instance const &instance) {
    stream << "( define ( problem " << instance.name << " )" << std::endl;

    stream << "  ( :domain " << instance.domain_name << " )" << std::endl;

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
