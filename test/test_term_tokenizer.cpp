#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <vector>

#include "tokenizer/term_tokenizer.hpp"

using namespace tok;

TEST_CASE("TermTokenizer")
{
    std::string str("a 1 12 w0rd, token-izer. pup's, U.S.a., us., hel.lo");
    TermTokenizer tokenizer(str);
    REQUIRE(std::vector<std::string>(tokenizer.begin(), tokenizer.end())
            == std::vector<std::string>{
                "a", "1", "12", "w0rd", "token", "izer", "pup", "USa", "us", "hel", "lo"});
}
