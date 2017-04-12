%{ /* -*- C++ -*- */
#include <iostream>
#include <cstdlib>
#include "scanner.hh"
#include "driver.hh"
#include "parser.bison.hh"
#include "location.hh"

// Ignore some warnings in the auto-generated code:
#pragma GCC diagnostic ignored "-Wsign-compare"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-register"
#endif

#define yyterminate() return pddl_parser::Parser::make_END(driver.location)

/* This is executed with every call to yylex. We just use it to keep
* the location updated.
*/
#define YY_USER_ACTION driver.incrementLocation(yyleng);
%}

%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="PDDL_"

%%

"("  { return pddl_parser::Parser::make_OPEN_PARENS(driver.location); }

")"  { return pddl_parser::Parser::make_CLOSE_PARENS(driver.location); }

"define" { return pddl_parser::Parser::make_DEFINEKW(driver.location); }

"domain" { return pddl_parser::Parser::make_DOMAINKW(driver.location); }

":domain" { return pddl_parser::Parser::make_DOMAINREFKW(driver.location); }

"problem" { return pddl_parser::Parser::make_PROBLEMKW(driver.location); }

":init" { return pddl_parser::Parser::make_INITKW(driver.location); }

":goal" { return pddl_parser::Parser::make_GOALKW(driver.location); }

":requirements" { return pddl_parser::Parser::make_REQUIREMENTSKW(driver.location); }

":types" { return pddl_parser::Parser::make_TYPESKW(driver.location); }

"number" { return pddl_parser::Parser::make_NUMBERKW(driver.location); }

":constants" { return pddl_parser::Parser::make_CONSTANTSKW(driver.location); }

":predicates" { return pddl_parser::Parser::make_PREDICATESKW(driver.location); }

":functions" { return pddl_parser::Parser::make_FUNCTIONSKW(driver.location); }

":objects" { return pddl_parser::Parser::make_OBJECTSKW(driver.location); }

":action" { return pddl_parser::Parser::make_ACTIONKW(driver.location); }

":parameters" { return pddl_parser::Parser::make_PARAMETERSKW(driver.location); }

":precondition" { return pddl_parser::Parser::make_PRECONDITIONKW(driver.location); }

":effect" { return pddl_parser::Parser::make_EFFECTKW(driver.location); }

"and" { return pddl_parser::Parser::make_AND(driver.location); }

"not" { return pddl_parser::Parser::make_NOT(driver.location); }

"<"  { return pddl_parser::Parser::make_L(driver.location); }

"<="  { return pddl_parser::Parser::make_LEQ(driver.location); }

"="  { return pddl_parser::Parser::make_EQ(driver.location); }

">="  { return pddl_parser::Parser::make_GEQ(driver.location); }

">"  { return pddl_parser::Parser::make_G(driver.location); }

"-"  { return pddl_parser::Parser::make_MINUS(driver.location); }

"+"  { return pddl_parser::Parser::make_PLUS(driver.location); }

"*"  { return pddl_parser::Parser::make_TIMES(driver.location); }

"/"  { return pddl_parser::Parser::make_DIV(driver.location); }

"assign" { return pddl_parser::Parser::make_ASSIGN(driver.location); }

"increase" { return pddl_parser::Parser::make_INCREASE(driver.location); }

"decrease" { return pddl_parser::Parser::make_DECREASE(driver.location); }

"scale-up" { return pddl_parser::Parser::make_SCALEUP(driver.location); }

"scale-down" { return pddl_parser::Parser::make_SCALEDOWN(driver.location); }

"forall" { return pddl_parser::Parser::make_FORALL(driver.location); }

"exists" { return pddl_parser::Parser::make_EXISTS(driver.location); }

"when" { return pddl_parser::Parser::make_WHEN(driver.location); }

"imply" { return pddl_parser::Parser::make_IMPLY(driver.location); }

":"?[a-zA-Z][a-zA-Z0-9\-_]* {
    return pddl_parser::Parser::make_NAME(yytext, driver.location);
}

"?"[a-zA-Z][a-zA-Z0-9\-_\[\]]* {
    return pddl_parser::Parser::make_VARIABLE(yytext, driver.location);
}

"-"?[0-9]*[.]?[0-9]* {
    return pddl_parser::Parser::make_NUMBER(atof(yytext), driver.location);
}

";".*  { /* Comment. Will match until EOL */ }

\n+    { driver.incrementLocationLine(yyleng); }

. {}

%%
