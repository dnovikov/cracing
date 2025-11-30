#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "vehicle.hpp"

TEST_CASE("Vehicle constructor", "[Vehicle][Constructor]") {
    SECTION("Default constructor initializes all properties correctly") {
        Vehicle v(1, 2, 3);
        int x, y;
        v.getxy(x, y);
        REQUIRE(x == 1);
        REQUIRE(y == 2);
        REQUIRE(v.get_speed() == 3);
    }
}

TEST_CASE("Vehicle getxy()", "[Vehicle][Method]") {
    SECTION("Vehicle getxy() method works") {
        Vehicle v(1, 2, 3);
        int x, y;
        v.getxy(x, y);
        REQUIRE(x == 1);
        REQUIRE(y == 2);
    }
}

TEST_CASE("Vehicle shift_x()", "[Vehicle][Method]") {
    SECTION("Vehicle offset is shifted to left") {
        Vehicle v(1, 2, 3);
        v.shift_x(-1);
        int x, y;
        v.getxy(x, y);
        REQUIRE(x == 0);
    }

    SECTION("Vehicle offset is shifted to right") {
        Vehicle v(1, 2, 3);
        v.shift_x(1);
        int x, y;
        v.getxy(x, y);
        REQUIRE(x == 2);
    }

    SECTION("Vehicle offset remains intact when adding 0") {
        Vehicle v(1, 2, 3);
        v.shift_x(0);
        int x, y;
        v.getxy(x, y);
        REQUIRE(x == 1);
    }
}

TEST_CASE("Vehicle speed_inc()", "[Vehicle][Method]") {
    SECTION("Vehicle speed increment adds 1") {
        Vehicle v(1, 2, 3);
        v.speed_inc(1);
        REQUIRE(v.get_speed() == 4);
    }

    SECTION("Vehicle speed increment subtracts 1") {
        Vehicle v(1, 2, 3);
        v.speed_inc(-1);
        REQUIRE(v.get_speed() == 2);
    }

    SECTION("Vehicle speed remains intact when adding 0") {
        Vehicle v(1, 2, 3);
        v.speed_inc(0);
        REQUIRE(v.get_speed() == 3);
    }
}

TEST_CASE("Vehicle tracks distance", "[Vehicle][Method]") {
    SECTION("Vehicle distance increases by 3 at the speed of 3") {
        Vehicle v(1, 2, 3);
        v.track_distance();
        REQUIRE(v.get_distance() == 3);
    }
}
