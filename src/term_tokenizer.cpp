#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/tokenizer.hpp>

#include "tokenizer/term_tokenizer.hpp"

namespace tok {


std::string TermTokenizer::transform(token_type const &tok)
{
    auto &val = tok.value();
    switch (tok.id()) {
    case AbbrToken: {
        std::string term;
        std::copy_if(
            val.begin(), val.end(), std::back_inserter(term), [](char ch) { return ch != '.'; });
        return term;
    }
    case PossessiveToken:
        return std::string(val.begin(), std::find(val.begin(), val.end(), '\''));
    default:
        return std::string(val.begin(), val.end());
    }
}
} // namespace tok