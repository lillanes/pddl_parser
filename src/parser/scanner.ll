%{ /* -*- C++ -*- */
#include <iostream>
#include <cstdlib>

#include <parser.bison.hh>
#include <location.hh>

#include "scanner.hh"

// Ignore some warnings in the auto-generated code:
#pragma GCC diagnostic ignored "-Wsign-compare"
#ifdef __clang__
#pragma clang diagnostic ignored "-Wdeprecated-register"
#endif

#define yyterminate() return pddl_parser::Parser::make_END(location)

/* This is executed with every call to yylex. We just use it to keep
* the location updated.
*/
#define YY_USER_ACTION increment_location(yyleng);
%}

%option caseless
%option nodefault
%option noyywrap
%option c++
%option yyclass="Scanner"
%option prefix="PDDL_"

%%

"("  { return pddl_parser::Parser::make_OPEN_PARENS(location); }

")"  { return pddl_parser::Parser::make_CLOSE_PARENS(location); }

"define" { return pddl_parser::Parser::make_DEFINEKW(location); }

"domain" { return pddl_parser::Parser::make_DOMAINKW(location); }

":domain" { return pddl_parser::Parser::make_DOMAINREFKW(location); }

"problem" { return pddl_parser::Parser::make_PROBLEMKW(location); }

":init" { return pddl_parser::Parser::make_INITKW(location); }

":goal" { return pddl_parser::Parser::make_GOALKW(location); }

":requirements" { return pddl_parser::Parser::make_REQUIREMENTSKW(location); }

":types" { return pddl_parser::Parser::make_TYPESKW(location); }

"number" { return pddl_parser::Parser::make_NUMBERKW(location); }

":constants" { return pddl_parser::Parser::make_CONSTANTSKW(location); }

":predicates" { return pddl_parser::Parser::make_PREDICATESKW(location); }

":functions" { return pddl_parser::Parser::make_FUNCTIONSKW(location); }

":objects" { return pddl_parser::Parser::make_OBJECTSKW(location); }

":action" { return pddl_parser::Parser::make_ACTIONKW(location); }

":parameters" { return pddl_parser::Parser::make_PARAMETERSKW(location); }

":precondition" { return pddl_parser::Parser::make_PRECONDITIONKW(location); }

":effect" { return pddl_parser::Parser::make_EFFECTKW(location); }

":metric" { return pddl_parser::Parser::make_METRICKW(location); }

"maximize" { return pddl_parser::Parser::make_MAXIMIZE(location); }

"minimize" { return pddl_parser::Parser::make_MINIMIZE(location); }

"and" { return pddl_parser::Parser::make_AND(location); }

"not" { return pddl_parser::Parser::make_NOT(location); }

"<"  { return pddl_parser::Parser::make_L(location); }

"<="  { return pddl_parser::Parser::make_LEQ(location); }

"="  { return pddl_parser::Parser::make_EQ(location); }

">="  { return pddl_parser::Parser::make_GEQ(location); }

">"  { return pddl_parser::Parser::make_G(location); }

"-"  { return pddl_parser::Parser::make_MINUS(location); }

"+"  { return pddl_parser::Parser::make_PLUS(location); }

"*"  { return pddl_parser::Parser::make_TIMES(location); }

"/"  { return pddl_parser::Parser::make_DIV(location); }

"assign" { return pddl_parser::Parser::make_ASSIGN(location); }

"increase" { return pddl_parser::Parser::make_INCREASE(location); }

"decrease" { return pddl_parser::Parser::make_DECREASE(location); }

"scale-up" { return pddl_parser::Parser::make_SCALEUP(location); }

"scale-down" { return pddl_parser::Parser::make_SCALEDOWN(location); }

"forall" { return pddl_parser::Parser::make_FORALL(location); }

"exists" { return pddl_parser::Parser::make_EXISTS(location); }

"when" { return pddl_parser::Parser::make_WHEN(location); }

"imply" { return pddl_parser::Parser::make_IMPLY(location); }

":"?[a-zA-Z][a-zA-Z0-9\-_]* {
    int index = 0;
    while(yytext[index] != 0) {
        yytext[index] = tolower(yytext[index]);
        ++index;
    }
    return pddl_parser::Parser::make_NAME(yytext, location);
}

"?"[a-zA-Z][a-zA-Z0-9\-_\[\]]* {
    int index = 0;
    while(yytext[index] != 0) {
        yytext[index] = tolower(yytext[index]);
        ++index;
    }
    return pddl_parser::Parser::make_VARIABLE(yytext, location);
}

"-"?[0-9]*[.]?[0-9]* {
    return pddl_parser::Parser::make_NUMBER(atof(yytext), location);
}

";".*  { /* Comment. Will match until EOL */ }

\n+    { increment_location_line(yyleng); }

. {}

%%
