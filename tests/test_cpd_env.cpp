#include "catch.hpp"

#include "environment.h"
#include "lib_cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_environment", "[cpd PureData wrapper]")
{
    SECTION("version")
    {
        REQUIRE(cpd_version_major() == 0);
        REQUIRE(cpd_version_minor() >= 47);
        REQUIRE(cpd_version_bugfix() >= 0);
    }
}
