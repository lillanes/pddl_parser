#include <utility>

#include "instance.hh"

namespace pddl_parser {

Instance::Instance(std::string &&name,
                   Domain &domain,
                   std::deque<std::string> &&requirements,
                   std::deque<TypedName> &&objects,
                   State &&init,
                   std::unique_ptr<Condition> &&goal)
    : name(std::move(name)),
      domain(domain),
      requirements(std::move(requirements)),
      objects(std::move(objects)),
      init(std::move(init)),
      goal(std::move(goal)) {
}

} // namespace pddl_parser
