#ifndef SCANNER_HH
#define SCANNER_HH


#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer PDDL_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL pddl_parser::Parser::symbol_type pddl_parser::Scanner::get_next_token()

#include "parser.bison.hh"

namespace pddl_parser {

class Driver;

class Scanner : public yyFlexLexer {
public:
    Scanner(Driver &driver)
        : driver(driver) {
    }
    virtual ~Scanner() {}
    virtual pddl_parser::Parser::symbol_type get_next_token();

private:
    Driver &driver;
};

} // PDDL

#endif // SCANNER_HH
