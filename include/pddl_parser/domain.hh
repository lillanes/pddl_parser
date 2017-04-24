#ifndef PDDL_PARSER_DOMAIN_HH
#define PDDL_PARSER_DOMAIN_HH

#include <deque>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

#include "action.hh"
#include "function.hh"
#include "predicate.hh"
#include "typed_name.hh"

namespace pddl_parser {

class Domain {
    friend class Parser;
    friend class Instance;

    friend class ObjectFetcher;
    friend class TypeChecker;
    friend class TypeMembersFetcher;

    std::string name;
    std::unordered_set<std::string> requirements;
    std::unordered_map<std::string,TypedName> types;
    std::unordered_map<std::string,TypedName> constants;
    std::unordered_map<std::string,Predicate> predicates;
    std::unordered_map<std::string,Function> functions;
    std::unordered_map<std::string,Action> actions;

    void set_name(std::string &&name);
    void set_requirements(std::deque<std::string> &&requirements);
    void set_types(std::deque<TypedName> &&types);
    void set_constants(std::deque<TypedName> &&constants);
    void set_predicates(std::deque<Predicate> &&predicates);
    void set_functions(std::deque<Function> &&functions);

    Predicate const& get_predicate(std::string &name) const;
    Function const& get_function(std::string &name) const;
    TypedName const& get_constant(std::string &name) const;

public:
    Domain() = default;
    Domain(std::string &&name,
           std::deque<std::string> &&requirements,
           std::deque<TypedName> &&types,
           std::deque<TypedName> &&constants,
           std::deque<Predicate> &&predicates,
           std::deque<Function> &&functions,
           std::deque<Action> &&actions);

    void add_action(Action &&action);

    bool validate() const;

    std::string const & get_name() const;
    std::unordered_map<std::string,Predicate> const & get_predicates() const;
    std::unordered_map<std::string,Function> const & get_functions() const;
    std::unordered_map<std::string,Action> const & get_actions() const;

    friend std::ostream& operator<<(std::ostream &stream, Domain const &domain);

};

} // namespace pddl_parser

#endif // PDDL_PARSER_DOMAIN_HH
