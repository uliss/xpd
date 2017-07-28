#include "catch.hpp"

#include "cpd/cpd.h"

#include <string>

static int init = cpd_init();

TEST_CASE("cpd_atom", "[cpd PureData wrapper]")
{
    SECTION("init")
    {
        auto a0 = cpd_atom_float_new(123);
        REQUIRE(cpd_atom_float(a0) == 123);
        REQUIRE(cpd_atom_is_float(a0));
        REQUIRE_FALSE(cpd_atom_is_symbol(a0));
        REQUIRE(cpd_atom_symbol(a0) == 0);

        cpd_atom_set_float(a0, -200);
        REQUIRE(cpd_atom_float(a0) == -200);

        cpd_atom_set_string(a0, "ABC");
        REQUIRE(cpd_atom_float(a0) == 0);
        REQUIRE(cpd_symbol_name(cpd_atom_symbol(a0)) == std::string("ABC"));

        cpd_atom_free(a0);

        auto a1 = cpd_atom_string_new("XYZ");
        REQUIRE(cpd_atom_is_symbol(a1));
        REQUIRE(cpd_symbol_name(cpd_atom_symbol(a1)) == std::string("XYZ"));
        cpd_atom_free(a1);
    }
}
