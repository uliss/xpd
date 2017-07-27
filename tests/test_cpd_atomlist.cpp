#include "catch.hpp"

#include "atomlist.h"
#include "lib_cpd.h"

static int i = cpd_init();

TEST_CASE("cpd_atomlist", "[cpd PureData wrapper]")
{
    SECTION("create")
    {
        SECTION("empty")
        {
            auto l = cpd_atomlist_new(0);
            REQUIRE(l);
            REQUIRE(cpd_atomlist_size(l) == 0);
            REQUIRE(cpd_atomlist_at(l, 0) == 0);
            REQUIRE(cpd_atomlist_at(l, 1) == 0);
        }

        SECTION("N")
        {
            auto l = cpd_atomlist_new(4);
            REQUIRE(l);
            REQUIRE(cpd_atomlist_size(l) == 4);
            REQUIRE(cpd_atom_is_float(cpd_atomlist_at(l, 0)));
            REQUIRE(cpd_atom_is_float(cpd_atomlist_at(l, 1)));
            REQUIRE(cpd_atom_is_float(cpd_atomlist_at(l, 2)));
            REQUIRE(cpd_atom_is_float(cpd_atomlist_at(l, 3)));

            REQUIRE(cpd_atom_float(cpd_atomlist_at(l, 0)) == 0);
            REQUIRE(cpd_atom_float(cpd_atomlist_at(l, 1)) == 0);
            REQUIRE(cpd_atom_float(cpd_atomlist_at(l, 2)) == 0);
            REQUIRE(cpd_atom_float(cpd_atomlist_at(l, 3)) == 0);
        }
    }

    SECTION("parse")
    {
        auto lst = cpd_atomlist_new_from_string("A,B");

        REQUIRE(lst);
        REQUIRE(cpd_atomlist_size(lst) == 3);
        REQUIRE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 0)));
        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 1)));
        REQUIRE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 2)));

        cpd_atomlist_free(lst);

        lst = cpd_atomlist_new_from_string("1 2.35,2 ; A");

        REQUIRE(lst);
        REQUIRE(cpd_atomlist_size(lst) == 6);

        REQUIRE(cpd_atom_is_float(cpd_atomlist_at(lst, 0)));
        REQUIRE(cpd_atom_float(cpd_atomlist_at(lst, 0)) == 1);

        REQUIRE(cpd_atom_is_float(cpd_atomlist_at(lst, 1)));
        REQUIRE(cpd_atom_float(cpd_atomlist_at(lst, 1)) == 2.35f);

        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 2)));
        REQUIRE_FALSE(cpd_atom_is_float(cpd_atomlist_at(lst, 2)));

        REQUIRE(cpd_atom_is_float(cpd_atomlist_at(lst, 3)));
        REQUIRE(cpd_atom_float(cpd_atomlist_at(lst, 3)) == 2);

        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 4)));
        REQUIRE_FALSE(cpd_atom_is_float(cpd_atomlist_at(lst, 4)));

        REQUIRE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 5)));
        REQUIRE(cpd_atom_symbol(cpd_atomlist_at(lst, 5)) == std::string("A"));

        cpd_atomlist_free(lst);

        lst = cpd_atomlist_new_from_string("$0-ABC");
        REQUIRE(cpd_atomlist_size(lst) == 1);
        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 0)));
        cpd_atomlist_free(lst);

        lst = cpd_atomlist_new_from_string("$1");
        REQUIRE(cpd_atomlist_size(lst) == 1);
        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 0)));
        REQUIRE_FALSE(cpd_atom_is_float(cpd_atomlist_at(lst, 0)));
        cpd_atomlist_free(lst);

        lst = cpd_atomlist_new_from_string("$ 1");
        REQUIRE(cpd_atomlist_size(lst) == 2);
        REQUIRE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 0)));
        REQUIRE(cpd_atom_symbol(cpd_atomlist_at(lst, 0)) == std::string("$"));
        REQUIRE(cpd_atom_is_float(cpd_atomlist_at(lst, 1)));
        cpd_atomlist_free(lst);

        lst = cpd_atomlist_new_from_string("$DOLLARS");
        REQUIRE(cpd_atomlist_size(lst) == 1);
        REQUIRE(cpd_atom_is_symbol(cpd_atomlist_at(lst, 0)));
        REQUIRE(cpd_atom_symbol(cpd_atomlist_at(lst, 0)) == std::string("$DOLLARS"));
        cpd_atomlist_free(lst);
    }
}
