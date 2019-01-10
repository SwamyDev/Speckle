#include "catch.hpp"

TEST_CASE("A succeeding test") {
    REQUIRE(true);
}

TEST_CASE("A failing test") {
    REQUIRE(false);
}
