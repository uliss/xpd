#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_object", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        auto cnv = cpd_root_canvas_new();

        auto obj1 = cpd_object_new(cnv, "float", 0, 0, 0);
        cpd_object_free(cnv, obj1);

        cpd_canvas_free(cnv);
    }

    SECTION("help path")
    {
        REQUIRE(cpd_object_help_path(nullptr) == std::string());

        auto cnv = cpd_root_canvas_new();

        // [+]
        auto obj1 = cpd_object_new(cnv, "+", 0, 0, 0);
        REQUIRE(cpd_object_help_path(obj1) == std::string("operators"));
        cpd_object_free(cnv, obj1);

        // [metro]
        auto obj2 = cpd_object_new(cnv, "metro", 0, 0, 0);
        REQUIRE(cpd_object_help_path(obj2) == std::string("metro"));
        cpd_object_free(cnv, obj2);

        cpd_canvas_free(cnv);
    }
}
