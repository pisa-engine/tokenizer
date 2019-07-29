#pragma once

#include <algorithm>
#include <cctype>
#include <string>
#include <string_view>
#include <vector>

#include <boost/iterator/filter_iterator.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/spirit/include/lex_lexertl.hpp>

namespace tok {

namespace lex = boost::spirit::lex;

static size_t const TermToken = lex::min_token_id + 1;
static size_t const AbbrToken = lex::min_token_id + 2;
static size_t const PossessiveToken = lex::min_token_id + 3;
static size_t const AnyToken = lex::min_token_id + 4;

template <typename Lexer>
struct tokens : lex::lexer<Lexer> {
    tokens()
    {
        this->self = lex::token_def<>(".", AnyToken)
                     | lex::token_def<>("([a-zA-Z]+\\.){2,}", AbbrToken)
                     | lex::token_def<>("[a-zA-Z0-9]+", TermToken)
                     | lex::token_def<>("[a-zA-Z0-9]+('[a-zA-Z]+)", PossessiveToken);
    }
};

class TermTokenizer {
   public:
    using token_type = lex::lexertl::
        token<std::string_view::const_iterator, boost::mpl::vector<>, boost::mpl::false_>;
    using lexer_type = lex::lexertl::actor_lexer<token_type>;

    TermTokenizer(std::string_view text)
        : text_(std::move(text)),
          first_(text_.begin()),
          last_(text_.end()){}

              [[nodiscard]] auto begin()
    {
        first_ = text_.begin();
        last_ = text_.end();
        return boost::make_transform_iterator(
            boost::make_filter_iterator(pred, lexer_.begin(first_, last_)), transform);
    }

    [[nodiscard]] auto end()
    {
        return boost::make_transform_iterator(boost::make_filter_iterator(pred, lexer_.end()),
                                              transform);
    }

   private:
    static bool pred(token_type const &tok) { return tok.id() != AnyToken; }
    static std::string transform(token_type const &tok);

    std::string_view text_;
    std::string_view::const_iterator first_;
    std::string_view::const_iterator last_;
    tokens<lexer_type> lexer_{};
};

} // namespace tok