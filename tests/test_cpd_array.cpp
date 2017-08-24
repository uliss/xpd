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
}
