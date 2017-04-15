%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.2"
%defines
%define parser_class_name { Parser }

// We are using C++, the parser will return objects.
%define api.token.constructor
%define api.value.type variant
%define api.namespace { pddl_parser }

/* We redefine the type used for filenames in a bison generated position.
 * Bison uses std::string, and making that const seems better than actually
 * storing a non-const copy of filenames somewhere.
 */
%define filename_type {const std::string}

%code requires
{
    #include <deque>
    #include <iterator>
    #include <memory>
    #include <string>
    #include <tuple>
    #include <unordered_set>
    #include <utility>

    #include "action.hh"
    #include "condition.hh"
    #include "domain.hh"
    #include "effect.hh"
    #include "function.hh"
    #include "numeric_expression.hh"
    #include "predicate.hh"
    #include "typed_name.hh"

    // Forward declarations
    namespace pddl_parser {
        class Scanner;
        class Driver;
    }
}

%code top
{
    #include <iostream>
    #include "scanner.hh"
    #include "parser.bison.hh"
    #include "driver.hh"

    // Our implementation of yylex:
    static pddl_parser::Parser::symbol_type yylex(pddl_parser::Scanner &scanner) {
        return scanner.get_next_token();
    }
}

// Parameters for /both/ the lexer and parser:
%param { pddl_parser::Scanner &scanner }
// Parameters only for the parser:
%parse-param { pddl_parser::Driver &driver }

%locations
%initial-action
{
    // Set the initial location filename. This won't change.
    @$.begin.filename = @$.end.filename = driver.location.begin.filename;
};

// For debugging:
// %define parse.assert
%define parse.trace
%define parse.error verbose

 // Allow no shift/reduce conflicts (they get flagged as errors):
%expect 0

%define api.token.prefix {TOK_}

%token
  END           0     "EOF"
  OPEN_PARENS         "("
  CLOSE_PARENS        ")"
  DEFINEKW            "define"
  DOMAINKW            "domain"
  DOMAINREFKW         ":domain"
  PROBLEMKW           "problem"
  REQUIREMENTSKW      ":requirements"
  TYPESKW             ":types"
  NUMBERKW            "number"
  CONSTANTSKW         ":constants"
  PREDICATESKW        ":predicates"
  FUNCTIONSKW         ":functions"
  ACTIONKW            ":action"
  PARAMETERSKW        ":parameters"
  PRECONDITIONKW      ":precondition"
  EFFECTKW            ":effect"
  OBJECTSKW           ":objects"
  INITKW              ":init"
  GOALKW              ":goal"
  AND                 "and"
  NOT                 "not"
  L                   "<"
  LEQ                 "<="
  EQ                  "="
  GEQ                 ">="
  G                   ">"
  MINUS               "-"
  PLUS                "+"
  TIMES               "*"
  DIV                 "/"
  ASSIGN              "assign"
  INCREASE            "increase"
  DECREASE            "decrease"
  SCALEUP             "scale-up"
  SCALEDOWN           "scale-down"
  FORALL              "forall (unsupported!)"
  EXISTS              "exists (unsupported!)"
  WHEN                "when (unsupported!)"
  IMPLY               "imply (unsupported!)"

%token <std::string>  NAME        "identifier"
%token <std::string>  VARIABLE    "variable"
%token <double>       NUMBER      "numeric value"

%type <std::string>
    require_key
    primitive_type
    type
    term
%type <std::deque<std::string>>
    require_def
    require_key_plus require_key_star
    name_plus name_star
    variable_plus variable_star
    term_plus term_star
%type <std::deque<TypedName>>
    types_def
    constants_def
    typed_list_name
    typed_list_variable

%type <Predicate> atomic_formula_skeleton
%type <std::deque<Predicate>>
    predicates_def
    atomic_formula_skeleton_plus
    atomic_formula_skeleton_star

%type <Function> atomic_function_skeleton
%type <std::deque<Function>>
    functions_def
    function_typed_list_atomic_function_skeleton
    atomic_function_skeleton_star
    atomic_function_skeleton_plus

%type <Action>
    action_def
    structure_def
%type <std::deque<Action>>
    structure_def_plus structure_def_star

%type <std::pair<Condition, std::deque<Effect>>> action_def_body

%type <Condition>
    goal_description
    literal
    f_comp
%type <std::deque<Condition>>
    goal_description_plus goal_description_star

%type <std::pair<std::string,std::deque<std::string>>> f_head

%type <NumericExpression> f_exp

%type <Effect> p_effect

%type <std::deque<Effect>>
    p_effect_plus p_effect_star
    effect

%type <std::tuple<std::deque<std::string>,
                  std::deque<TypedName>,
                  std::deque<TypedName>,
                  std::deque<Predicate>,
                  std::deque<Function>,
                  std::deque<Action>>>
    domain_parts

%start domain

%%

domain:
    "(" "define" "(" "domain" NAME ")"
    domain_parts ")"
{
    driver.set_domain(Domain(std::move($5),
                             std::move(std::get<0>($7)),
                             std::move(std::get<1>($7)),
                             std::move(std::get<2>($7)),
                             std::move(std::get<3>($7)),
                             std::move(std::get<4>($7)),
                             std::move(std::get<5>($7))));
}
;

/* This is more general than the BNF spec, as it allows for multiple definitions
   of the same part (e.g. types). It makes it LALR(1) parseable. */
domain_parts:
    require_def domain_parts
    {
        std::get<0>($2) = std::move($1);
        $$ = std::move($2);
    }
  | types_def domain_parts
    {
        std::get<1>($2) = std::move($1);
        $$ = std::move($2);
    }
  | constants_def domain_parts
    {
        std::get<2>($2) = std::move($1);
        $$ = std::move($2);
    }
  | predicates_def domain_parts
    {
        std::get<3>($2) = std::move($1);
        $$ = std::move($2);
    }
  | functions_def domain_parts
    {
        std::get<4>($2) = std::move($1);
        $$ = std::move($2);
    }
  | structure_def_star
    {
        std::get<5>($$) = std::move($1);
    }
  ;

require_def: "(" ":requirements" require_key_plus ")"
{
    $$ = std::move($3);
};

require_key: NAME
{
    $$ = std::move($1);
};

types_def: "(" ":types" typed_list_name ")"
{
    $$ = std::move($3);
};

constants_def: "(" ":constants" typed_list_name ")"
{
    $$ = std::move($3);
};

predicates_def: "(" ":predicates" atomic_formula_skeleton_plus ")"
{
    $$ = std::move($3);
};

atomic_formula_skeleton: "(" NAME typed_list_variable ")"
{
    $$ = Predicate(std::move($2), std::move($3));
};

functions_def: "(" ":functions"
    function_typed_list_atomic_function_skeleton ")"
{
    $$ = std::move($3);
};

atomic_function_skeleton: "(" NAME typed_list_variable ")"
{
    $$ = Function(std::move($2), std::move($3));
};

structure_def: action_def
{
    $$ = std::move($1);
};

action_def:
    "(" ":action" NAME
        ":parameters" "(" typed_list_variable ")"
        action_def_body ")"
    {
        $$ = Action(std::move($3),
                    std::move($6),
                    std::move($8.first),
                    std::move($8.second));
    }
    ;

action_def_body:
    %empty
    {
        $$ = std::make_pair<Condition,std::deque<Effect>>(nullptr, {});
    }
  | ":precondition" goal_description
    {
        $$ = std::make_pair<Condition,std::deque<Effect>>(std::move($2), {});
    }
  | ":effect" effect
    {
        $$ = std::make_pair<Condition,std::deque<Effect>>(nullptr,
                                                          std::move($2));
    }
  | ":precondition" goal_description
    ":effect" effect
    {
        $$ = std::make_pair<Condition,std::deque<Effect>>(std::move($2),
                                                          std::move($4));
    }
  ;

goal_description:
    "(" ")"
    {
        std::cout << "empty condition" << std::endl;
    }
  | literal
    {
        $$ = std::move($1);
    }
  | "(" "and" goal_description_star ")"
    {
        $$ = Condition(new Conjunction(std::move($3)));
    }
  | f_comp
    {
        $$ = std::move($1);
    }
  ;

literal:
    "(" NAME term_star ")"
    {
        $$ = Condition(new Literal(std::move($2), std::move($3)));
    }
  | "(" "not" "(" NAME term_star ")" ")"
    {
        $$ = Condition(new Literal(std::move($4), std::move($5), true));
    }
  ;

term:
    NAME
    {
        $$ = std::move($1);
    }
  | VARIABLE
    {
        $$ = std::move($1);
    }
  ;

f_exp:
     NUMBER
     {
         $$ = NumericExpression(new Number($1));
     }
  | "(" "+" f_exp f_exp ")"
     {
         $$ = NumericExpression(new BinaryExpression(BinaryOperator::PLUS,
                                                     std::move($3),
                                                     std::move($4)));
     }
  | "(" "-" f_exp f_exp ")"
    {
        $$ = NumericExpression(new BinaryExpression(BinaryOperator::MINUS,
                                                    std::move($3),
                                                    std::move($4)));
    }
  | "(" "*" f_exp f_exp ")"
    {
        $$ = NumericExpression(new BinaryExpression(BinaryOperator::TIMES,
                                                    std::move($3),
                                                    std::move($4)));
    }
  | "(" "/" f_exp f_exp ")"
    {
        $$ = NumericExpression(new BinaryExpression(BinaryOperator::DIV,
                                                    std::move($3),
                                                    std::move($4)));
    }
  | "(" "-" f_exp ")"
    {
        $$ = NumericExpression(new InverseExpression(std::move($3)));
    }
  | f_head
     {
         $$ = NumericExpression(new AtomicExpression(std::move($1.first),
                                                     std::move($1.second)));
     }
  ;

f_head:
    NAME
    {
        $$ = std::make_pair(std::move($1), std::deque<std::string>());
    }
  | "(" NAME term_star ")"
    {
        $$ = std::make_pair(std::move($2), std::move($3));
    }
  ;

f_comp:
    "(" "<" f_exp f_exp ")"
    {
        $$ = Condition(new NumericComparison(Comparator::LT,
                                             std::move($3),
                                             std::move($4)));
    }
  | "(" "<=" f_exp f_exp ")"
    {
        $$ = Condition(new NumericComparison(Comparator::LTE,
                                             std::move($3),
                                             std::move($4)));
    }
  | "(" "=" f_exp f_exp ")"
    {
        $$ = Condition(new NumericComparison(Comparator::EQ,
                                             std::move($3),
                                             std::move($4)));
    }
  | "(" ">=" f_exp f_exp ")"
    {
        $$ = Condition(new NumericComparison(Comparator::GTE,
                                             std::move($3),
                                             std::move($4)));
    }
  | "(" ">" f_exp f_exp ")"
    {
        $$ = Condition(new NumericComparison(Comparator::GT,
                                             std::move($3),
                                             std::move($4)));
    }
  ;

effect:
    "(" ")"
    {
        $$ = std::deque<Effect>();
    }
  | "(" "and" p_effect_star ")"
    {
        $$ = std::move($3);
    }
  ;

p_effect:
    "(" NAME term_star ")"
    {
        $$ = Effect(new AddEffect(std::move($2), std::move($3)));
    }
  | "(" "not" "(" NAME term_star ")" ")"
    {
        $$ = Effect(new DeleteEffect(std::move($4), std::move($5)));
    }
  | "(" "assign" f_head f_exp ")"
    {
        $$ = Effect(new NumericEffect(AssignmentOperator::ASSIGN,
                                      std::move($3.first),
                                      std::move($3.second),
                                      std::move($4)));
    }
  | "(" "scale-up" f_head f_exp ")"
    {
        $$ = Effect(new NumericEffect(AssignmentOperator::SCALE_UP,
                                      std::move($3.first),
                                      std::move($3.second),
                                      std::move($4)));
    }
  | "(" "scale-down" f_head f_exp ")"
    {
        $$ = Effect(new NumericEffect(AssignmentOperator::SCALE_DOWN,
                                      std::move($3.first),
                                      std::move($3.second),
                                      std::move($4)));
    }
  | "(" "increase" f_head f_exp ")"
    {
        $$ = Effect(new NumericEffect(AssignmentOperator::INCREASE,
                                      std::move($3.first),
                                      std::move($3.second),
                                      std::move($4)));
    }
  | "(" "decrease" f_head f_exp ")"
    {
        $$ = Effect(new NumericEffect(AssignmentOperator::DECREASE,
                                      std::move($3.first),
                                      std::move($3.second),
                                      std::move($4)));
    }
  ;

// lists:

type:
    primitive_type
    {
        $$ = std::move($1);
    }
  // | "(" "either" primitive_type_plus ")"
  ;

primitive_type: NAME
{
    $$ = std::move($1);
};

function_type: "number";

typed_list_name:
    name_star
    {
        for (std::string &s : $1) {
            $$.emplace_back(std::move(s));
        }
    }
  | name_plus "-" type typed_list_name
    {
        for (std::string &s : $1) {
            $4.emplace_back(std::move(s), std::string($3));
        }
        $$ = std::move($4);
    }
  ;

typed_list_variable:
    variable_star
    {
        for (std::string &s : $1) {
            $$.emplace_back(std::move(s));
        }
    }
  | variable_plus "-" type typed_list_variable
    {
        for (std::string &s : $1) {
            $$.emplace_back(std::move(s), std::string($3));
        }
        $$.insert($$.end(),
                  std::make_move_iterator($4.begin()),
                  std::make_move_iterator($4.end()));
    }
  ;

function_typed_list_atomic_function_skeleton:
    atomic_function_skeleton_star
    {
        $$ = std::move($1);
    }
  | atomic_function_skeleton_plus "-" function_type
        function_typed_list_atomic_function_skeleton
    {
        $$ = std::move($1);
        $$.insert($$.end(),
                  std::make_move_iterator($4.begin()),
                  std::make_move_iterator($4.end()));
    }
  ;

// regular expressions (kleene star, kleene plus):

require_key_plus: require_key require_key_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

require_key_star:
    require_key_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

name_plus: NAME name_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

name_star:
    name_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

variable_plus: VARIABLE variable_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

variable_star:
    variable_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

term_plus: term term_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

term_star:
    term_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

atomic_formula_skeleton_plus:
    atomic_formula_skeleton atomic_formula_skeleton_star
    {
        $2.emplace_front(std::move($1));
        $$ = std::move($2);
    };

atomic_formula_skeleton_star:
    atomic_formula_skeleton_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

atomic_function_skeleton_plus:
    atomic_function_skeleton atomic_function_skeleton_star
    {
        $2.emplace_front(std::move($1));
        $$ = std::move($2);
    };

atomic_function_skeleton_star:
    atomic_function_skeleton_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

structure_def_plus: structure_def structure_def_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

structure_def_star:
    structure_def_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

goal_description_plus: goal_description goal_description_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

goal_description_star:
    goal_description_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

p_effect_plus: p_effect p_effect_star
{
    $2.emplace_front(std::move($1));
    $$ = std::move($2);
};

p_effect_star:
    p_effect_plus
    {
        $$ = std::move($1);
    }
  | %empty {};

%%

void pddl_parser::Parser::error(const location &loc , const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << loc << "\n";
}
