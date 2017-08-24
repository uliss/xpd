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
        REQUIRE(cpd_array_find_by_name(cpd_symbol("array1")) == arr);
        REQUIRE(cpd_array_find_by_name(cpd_symbol("unknown")) == NULL);
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
        REQUIRE(cpd_array_set_plotstyle(NULL, CPD_ARRAY_STYLE_POLY) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("array1"), 0, 0);
        REQUIRE(cpd_array_linewidth(arr1) == 1);

        auto arr2 = cpd_array_new(cnv, cpd_symbol("array2"), 100, CPD_ARRAY_STYLE_POLY);
        REQUIRE(cpd_array_linewidth(arr2) == 2);
        REQUIRE(cpd_array_plotstyle(arr2) == CPD_ARRAY_STYLE_POLY);

        auto arr3 = cpd_array_new(cnv, cpd_symbol("array3"), 100, CPD_ARRAY_STYLE_POINTS);
        REQUIRE(cpd_array_linewidth(arr3) == 1);
        REQUIRE(cpd_array_plotstyle(arr3) == CPD_ARRAY_STYLE_POINTS);

        auto arr4 = cpd_array_new(cnv, cpd_symbol("array4"), 100, CPD_ARRAY_STYLE_BEZIER);
        REQUIRE(cpd_array_linewidth(arr4) == 1);
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_BEZIER);

        REQUIRE(cpd_array_set_linewidth(arr4, 1.2));
        REQUIRE(cpd_array_linewidth(arr4) == 1.2f);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_STYLE_POINTS));
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_POINTS);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_STYLE_POLY));
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_POLY);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_STYLE_BEZIER));
        REQUIRE(cpd_array_plotstyle(arr4) == CPD_ARRAY_STYLE_BEZIER);

        REQUIRE(cpd_array_set_plotstyle(arr4, CPD_ARRAY_HIDE_NAME) == 0);

        cpd_canvas_free(cnv);
    }

    SECTION("hidden name")
    {
        REQUIRE(cpd_array_hidden_name(NULL) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("array1"), 100, 0);
        REQUIRE(cpd_array_hidden_name(arr1) == 0);

        auto arr2 = cpd_array_new(cnv, cpd_symbol("array2"), 100, CPD_ARRAY_HIDE_NAME);
        REQUIRE(cpd_array_hidden_name(arr2) == 1);

        cpd_canvas_free(cnv);
    }

    SECTION("same name")
    {
        REQUIRE(cpd_array_hidden_name(NULL) == 0);

        auto cnv = cpd_patch_new();

        auto arr1 = cpd_array_new(cnv, cpd_symbol("same"), 100, 0);
        auto arr2 = cpd_array_new(cnv, cpd_symbol("same"), 100, 0);
        REQUIRE(arr1);
        REQUIRE(arr2);
        REQUIRE(arr1 != arr2);

        REQUIRE(cpd_array_find_by_name(cpd_symbol("same")) == arr1);

        cpd_canvas_free(cnv);
    }

    SECTION("data")
    {
        REQUIRE(cpd_array_at(NULL, 0) == NULL);

        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 5, 0);

        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 0)) == 0);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 1)) == 0);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 2)) == 0);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 3)) == 0);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 4)) == 0);

        REQUIRE(cpd_array_at(arr, 5) == NULL);
        REQUIRE(cpd_array_at(arr, 6) == NULL);

        cpd_array_element_set_float(cpd_array_at(arr, 0), 1);
        cpd_array_element_set_float(cpd_array_at(arr, 1), 2);
        cpd_array_element_set_float(cpd_array_at(arr, 2), 3);
        cpd_array_element_set_float(cpd_array_at(arr, 3), 4);
        cpd_array_element_set_float(cpd_array_at(arr, 4), 5);

        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 0)) == 1);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 1)) == 2);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 2)) == 3);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 3)) == 4);
        REQUIRE(cpd_array_element_float(cpd_array_at(arr, 4)) == 5);

        cpd_canvas_free(cnv);
    }

    SECTION("copy data")
    {
        REQUIRE_FALSE(cpd_array_copy_data(NULL, 0, 5));

        t_cpd_float buf[5] = { 1, 1, 1, 1, 1 };

        auto cnv = cpd_patch_new();
        auto arr = cpd_array_new(cnv, cpd_symbol("array1"), 3, 0);
        REQUIRE(cpd_array_copy_data(arr, buf, 5));

        // copy only 3 first elements
        REQUIRE(buf[0] == 0);
        REQUIRE(buf[1] == 0);
        REQUIRE(buf[2] == 0);
        REQUIRE(buf[3] == 1);
        REQUIRE(buf[4] == 1);

        cpd_canvas_free(cnv);
    }
}
