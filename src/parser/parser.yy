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
;
%token <std::string>  NAME        "identifier"
%token <std::string>  VARIABLE    "variable"
%token <double>       NUMBER      "numeric value"

%start domain

%%

domain:
    "(" "define" "(" "domain" NAME ")"
    domain_parts ")"
;

/* This is more general than the BNF spec, as it allows for multiple definitions
   of the same part (e.g. types). It makes it LALR(1) parseable. */
domain_parts:
    require_def domain_parts
  | types_def domain_parts
  | constants_def domain_parts
  | predicates_def domain_parts
  | functions_def domain_parts
  | structure_def_star
  ;

//============

// f_exp:
//     "(" "-" f_exp ")"
//   | "(" "+" f_exp f_exp ")"
//   | "(" "-" f_exp f_exp ")"
//   | "(" "*" f_exp f_exp ")"
//   | "(" "/" f_exp f_exp ")"
//   | NUMBER
//   ;

//============

require_def: "(" ":requirements" require_key_plus ")";

require_key: NAME;

types_def: "(" ":types" typed_list_name ")";

constants_def: "(" ":constants" typed_list_name ")";

predicates_def: "(" ":predicates" atomic_formula_skeleton_plus ")";

atomic_formula_skeleton: "(" NAME typed_list_variable ")";

functions_def: "(" ":functions"
    function_typed_list_atomic_function_skeleton ")";

atomic_function_skeleton: "(" NAME typed_list_variable ")";

structure_def: action_def;

action_def:
    "(" ":action" NAME
        ":parameters" "(" typed_list_variable ")"
        action_def_body ")"
    ;

action_def_body:
    %empty
  | ":precondition" goal_description
  | ":effect" effect
  | ":precondition" goal_description
    ":effect" effect
  ;

goal_description:
    "(" ")"
  | literal
  | "(" "and" goal_description_star ")"
  | f_comp
  ;

literal:
    "(" NAME term_star ")"
  | "(" "not" "(" NAME term_star ")" ")"
  ;

term: NAME | VARIABLE;

f_exp:
     NUMBER
  | "(" "+" f_exp f_exp ")"
  | "(" "-" f_exp f_exp ")"
  | "(" "*" f_exp f_exp ")"
  | "(" "/" f_exp f_exp ")"
  | "(" "-" f_exp ")"
  | f_head
  ;

f_head:
    NAME
  | "(" NAME term_star ")"
  ;

f_comp:
    "(" "<" f_exp f_exp ")"
  | "(" "<=" f_exp f_exp ")"
  | "(" "=" f_exp f_exp ")"
  | "(" ">=" f_exp f_exp ")"
  | "(" ">" f_exp f_exp ")"
  ;

effect:
    "(" ")"
  | "(" "and" p_effect_star ")"
  ;

p_effect:
    literal
  | "(" "assign" f_head f_exp ")"
  | "(" "scale-up" f_head f_exp ")"
  | "(" "scale-down" f_head f_exp ")"
  | "(" "increase" f_head f_exp ")"
  | "(" "decrease" f_head f_exp ")"
  ;

// lists:

type:
    primitive_type
  // | "(" "either" primitive_type_plus ")"
  ;

primitive_type: NAME;

function_type: "number";

typed_list_name:
    name_star
  | name_plus "-" type typed_list_name
  ;

typed_list_variable:
    variable_star
  | variable_plus "-" type typed_list_variable
  ;

function_typed_list_atomic_function_skeleton:
    atomic_function_skeleton_star
  | atomic_function_skeleton_plus "-" function_type
        function_typed_list_atomic_function_skeleton
  ;

// regular expressions (kleene star, kleene plus):

require_key_plus: require_key require_key_star;

require_key_star: require_key_plus | %empty;

name_plus: NAME name_star;

name_star: name_plus | %empty;

variable_plus: VARIABLE variable_star;

variable_star: variable_plus | %empty;

atomic_formula_skeleton_plus:
    atomic_formula_skeleton atomic_formula_skeleton_star;

atomic_formula_skeleton_star: atomic_formula_skeleton_plus | %empty;

atomic_function_skeleton_plus:
    atomic_function_skeleton atomic_function_skeleton_star;

atomic_function_skeleton_star: atomic_function_skeleton_plus | %empty;

structure_def_plus: structure_def structure_def_star;

structure_def_star: structure_def_plus | %empty;

goal_description_plus: goal_description goal_description_star;

goal_description_star: goal_description_plus | %empty;

term_plus: term term_star;

term_star: term_plus | %empty;

p_effect_plus: p_effect p_effect_star;

p_effect_star: p_effect_plus | %empty;

%%

void pddl_parser::Parser::error(const location &loc , const std::string &err_message) {
   std::cerr << "Error: " << err_message << " at " << loc << "\n";
}
