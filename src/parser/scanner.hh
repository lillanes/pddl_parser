#ifndef PDDL_PARSER_SCANNER_HH
#define PDDL_PARSER_SCANNER_HH


#if ! defined(yyFlexLexerOnce)
#undef yyFlexLexer
#define yyFlexLexer PDDL_FlexLexer
#include <FlexLexer.h>
#endif

#undef YY_DECL
#define YY_DECL pddl_parser::Parser::symbol_type pddl_parser::Scanner::get_next_token()

#include <parser.bison.hh>

namespace pddl_parser {

class Scanner : public yyFlexLexer {
    friend class Parser;
public:
    Scanner() = default;
    virtual pddl_parser::Parser::symbol_type get_next_token();

    void initialize_location(std::string const &filename) {
        this->filename = filename;
        location.initialize(&this->filename);
    }

private:
    pddl_parser::location location;
    std::string filename;

    void increment_location(size_t loc) {
        location.step();
        location += loc;
    }

    void increment_location_line(size_t loc) {
        location.lines(loc);
    }
};

} // namespace pddl_parser

#endif // PDDL_PARSER_SCANNER_HH
