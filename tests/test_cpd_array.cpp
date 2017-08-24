#include "catch.hpp"

#include "cpd/cpd.h"
#include "cpd/cpd_catcher.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_array", "[cpd PureData wrapper]")
{
    SECTION("create")
    {
        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 200, 0);
        REQUIRE(cpd_array_size(arr) == 200);
        cpd_array_free(cnv, arr);

        cpd_array_free(NULL, arr);
        cpd_array_free(cnv, NULL);

        REQUIRE(cpd_array_new(NULL, cpd_symbol("array1"), 200, 0) == nullptr);
        cpd_canvas_free(cnv);
    }

    SECTION("size")
    {
        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 0, 0);
        REQUIRE(cpd_array_size(arr) == 1);
        REQUIRE(cpd_array_size(NULL) == 0);
        cpd_canvas_free(cnv);
    }

    SECTION("linewidth")
    {
        REQUIRE(cpd_array_linewidth(NULL) == 0);
        REQUIRE(cpd_array_set_linewidth(NULL, 0) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("array1"), 0, 0);
        REQUIRE(cpd_array_linewidth(arr1) == 1);

        auto arr2 = cpd_array_new(cnv, cpd_symbol("array2"), 100, CPD_ARRAY_STYLE_POLY);
        REQUIRE(cpd_array_linewidth(arr2) == 2);

        auto arr3 = cpd_array_new(cnv, cpd_symbol("array3"), 100, CPD_ARRAY_STYLE_POINTS);
        REQUIRE(cpd_array_linewidth(arr3) == 1);

        auto arr4 = cpd_array_new(cnv, cpd_symbol("array4"), 100, CPD_ARRAY_STYLE_BEZIER);
        REQUIRE(cpd_array_linewidth(arr4) == 1);

        REQUIRE(cpd_array_set_linewidth(arr4, 1.2));
        REQUIRE(cpd_array_linewidth(arr4) == 1.2f);

        cpd_canvas_free(cnv);
    }
}
