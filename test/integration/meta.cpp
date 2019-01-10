#include "catch.hpp"

TEST_CASE("A failing test") {
    REQUIRE(false);
}

TEST_CASE("A succeeding test") {
    REQUIRE(true);
}

