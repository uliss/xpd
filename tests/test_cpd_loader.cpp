#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_loader", "[cpd PureData wrapper]")
{
    SECTION("load_library")
    {
        REQUIRE(cpd_load_library(cpd_symbol("not-exists")) == 0);
    }
}
