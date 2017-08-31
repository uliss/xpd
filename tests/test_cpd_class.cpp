#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_class", "[cpd PureData wrapper]")
{
    SECTION("class_name")
    {
        REQUIRE(cpd_class_name(nullptr) == std::string(""));

        auto cnv = cpd_patch_new();

        auto obj_f = cpd_object_new(cnv, "f", NULL, 0, 0);
        REQUIRE(cpd_class_name(cpd_object_class(obj_f)) == std::string("float"));

        auto obj_f2 = cpd_object_new(cnv, "float", NULL, 0, 0);
        REQUIRE(cpd_class_name(cpd_object_class(obj_f2)) == std::string("float"));

        cpd_canvas_free(cnv);
    }

    SECTION("method_count")
    {
        REQUIRE(cpd_class_method_count(nullptr) == 0);

        auto cnv = cpd_patch_new();

        auto obj_f = cpd_object_new(cnv, "readsf~", NULL, 0, 0);
        REQUIRE(cpd_class_method_count(cpd_object_class(obj_f)) == 5);

        cpd_canvas_free(cnv);
    }
}
