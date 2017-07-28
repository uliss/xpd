#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_canvas", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        REQUIRE(cpd_canvas_current() == 0);
        REQUIRE(cpd_root_canvas_count() == 3);
        REQUIRE(cpd_root_canvas_last() != 0);

        auto c0 = cpd_root_canvas_new();
        REQUIRE(c0);
        REQUIRE(cpd_root_canvas_count() == 4);
        REQUIRE(cpd_root_canvas_at(0) == c0);
        REQUIRE(cpd_canvas_current() == c0);
        REQUIRE(cpd_canvas_name(c0) == std::string("Untitled-1"));

        cpd_canvas_free(c0);
        REQUIRE(cpd_root_canvas_count() == 3);
    }

    SECTION("multiple")
    {
        REQUIRE(cpd_root_canvas_count() == 3);

        auto c0 = cpd_root_canvas_new();
        REQUIRE(cpd_root_canvas_count() == 4);
        REQUIRE(c0);
        REQUIRE(cpd_canvas_name(c0) == std::string("Untitled-2"));

        auto c1 = cpd_root_canvas_new();
        REQUIRE(c1);
        REQUIRE(cpd_root_canvas_count() == 5);
        REQUIRE(cpd_canvas_name(c1) == std::string("Untitled-3"));

        cpd_canvas_free(c1);
        REQUIRE(cpd_root_canvas_count() == 4);

        cpd_canvas_free(c0);
        REQUIRE(cpd_root_canvas_count() == 3);
    }

    SECTION("name")
    {
        REQUIRE(cpd_canvas_name(cpd_root_canvas_at(0)) == std::string("_float_array_template"));
        REQUIRE(cpd_canvas_name(cpd_root_canvas_at(1)) == std::string("_float_template"));
        REQUIRE(cpd_canvas_name(cpd_root_canvas_at(2)) == std::string("_text_template"));
    }
}
