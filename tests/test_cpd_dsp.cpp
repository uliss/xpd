#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_dsp", "[cpd PureData wrapper]")
{
    SECTION("dsp on off")
    {
        cpd_dsp_start();
        cpd_dsp_stop();
    }
}
