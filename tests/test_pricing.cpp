#include <catch2/catch_test_macros.hpp>
#include <pricing.hpp>

TEST_CASE("full 8-decimal strings", "[parse]"){
    REQUIRE(parse_fixed8("76162.18000000") == 7616218000000);
    REQUIRE(parse_fixed8("77320.42000000") == 7732042000000);
    REQUIRE(parse_fixed8("77501.17000000") == 7750117000000);
}

TEST_CASE("short fractions are padded", "[parse]"){
    REQUIRE(parse_fixed8("8.2") == 820000000);
    REQUIRE(parse_fixed8("8.20000000") == 820000000);
}

TEST_CASE("no decimal point", "[parse]"){
    REQUIRE(parse_fixed8("77320") == 7732000000000);
}

TEST_CASE("zero and sub-unit quantities", "[parse]"){
    REQUIRE(parse_fixed8("0.00000001") == 1);
    REQUIRE(parse_fixed8("0.00000000") == 0);
    REQUIRE(parse_fixed8("0.00032000") == 32000);
}