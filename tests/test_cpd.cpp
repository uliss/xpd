#include "catch.hpp"

#include "lib_cpd.h"

TEST_CASE("cpd", "[cpd PureData wrapper]")
{
    SECTION("cpd_canvas_last")
    {
        cpd_init();
        REQUIRE(cpd_root_canvas_count() == 3);
        REQUIRE(cpd_root_canvas_last() != 0);
        REQUIRE(cpd_root_canvas_at(0) != 0);
        REQUIRE(cpd_root_canvas_at(1) != 0);
        REQUIRE(cpd_root_canvas_at(2) != 0);
        REQUIRE(cpd_root_canvas_at(3) == 0);
        REQUIRE(cpd_root_canvas_at(4) == 0);
        REQUIRE(cpd_root_canvas_at(0) != cpd_root_canvas_at(1));
        REQUIRE(cpd_root_canvas_at(1) != cpd_root_canvas_at(2));
        REQUIRE(cpd_root_canvas_at(0) != cpd_root_canvas_at(2));
        REQUIRE(cpd_root_canvas_at(2) == cpd_root_canvas_last());
        REQUIRE(cpd_root_canvas_next(cpd_root_canvas_at(0)) == cpd_root_canvas_at(1));
        REQUIRE(cpd_root_canvas_next(0) == 0);

        REQUIRE(cpd_canvas_name(cpd_root_canvas_at(0)) == std::string("_float_array_template"));
        REQUIRE(cpd_canvas_name(cpd_root_canvas_at(1)) == std::string("_float_template"));
        REQUIRE(cpd_canvas_name(cpd_root_canvas_at(2)) == std::string("_text_template"));

        REQUIRE(!cpd_canvas_free(0));
        REQUIRE(cpd_canvas_free(cpd_root_canvas_at(2)));
        REQUIRE(cpd_root_canvas_count() == 2);
    }
}
