#include "catch.hpp"

#include "cpd/cpd.h"

static int i = cpd_init();

TEST_CASE("cpd_list", "[cpd PureData wrapper]")
{
    SECTION("create")
    {
        SECTION("empty")
        {
            auto l = cpd_list_new(0);
            REQUIRE(l);
            REQUIRE(cpd_list_size(l) == 0);
            REQUIRE(cpd_list_at(l, 0) == 0);
            REQUIRE(cpd_list_at(l, 1) == 0);
        }

        SECTION("N")
        {
            auto l = cpd_list_new(4);
            REQUIRE(l);
            REQUIRE(cpd_list_size(l) == 4);
            REQUIRE(cpd_atom_is_float(cpd_list_at(l, 0)));
            REQUIRE(cpd_atom_is_float(cpd_list_at(l, 1)));
            REQUIRE(cpd_atom_is_float(cpd_list_at(l, 2)));
            REQUIRE(cpd_atom_is_float(cpd_list_at(l, 3)));

            REQUIRE(cpd_atom_get_float(cpd_list_at(l, 0)) == 0);
            REQUIRE(cpd_atom_get_float(cpd_list_at(l, 1)) == 0);
            REQUIRE(cpd_atom_get_float(cpd_list_at(l, 2)) == 0);
            REQUIRE(cpd_atom_get_float(cpd_list_at(l, 3)) == 0);
        }
    }

    SECTION("parse")
    {
        auto lst = cpd_list_new_from_string("A,B");

        REQUIRE(lst);
        REQUIRE(cpd_list_size(lst) == 3);
        REQUIRE(cpd_atom_is_symbol(cpd_list_at(lst, 0)));
        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_list_at(lst, 1)));
        REQUIRE(cpd_atom_is_symbol(cpd_list_at(lst, 2)));

        cpd_list_free(lst);

        lst = cpd_list_new_from_string("1 2.35,2 ; A");

        REQUIRE(lst);
        REQUIRE(cpd_list_size(lst) == 6);

        REQUIRE(cpd_atom_is_float(cpd_list_at(lst, 0)));
        REQUIRE(cpd_atom_get_float(cpd_list_at(lst, 0)) == 1);

        REQUIRE(cpd_atom_is_float(cpd_list_at(lst, 1)));
        REQUIRE(cpd_atom_get_float(cpd_list_at(lst, 1)) == 2.35f);

        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_list_at(lst, 2)));
        REQUIRE_FALSE(cpd_atom_is_float(cpd_list_at(lst, 2)));

        REQUIRE(cpd_atom_is_float(cpd_list_at(lst, 3)));
        REQUIRE(cpd_atom_get_float(cpd_list_at(lst, 3)) == 2);

        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_list_at(lst, 4)));
        REQUIRE_FALSE(cpd_atom_is_float(cpd_list_at(lst, 4)));

        REQUIRE(cpd_atom_is_symbol(cpd_list_at(lst, 5)));
        REQUIRE(cpd_symbol_name(cpd_atom_get_symbol(cpd_list_at(lst, 5))) == std::string("A"));

        cpd_list_free(lst);

        lst = cpd_list_new_from_string("$0-ABC");
        REQUIRE(cpd_list_size(lst) == 1);
        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_list_at(lst, 0)));
        cpd_list_free(lst);

        lst = cpd_list_new_from_string("$1");
        REQUIRE(cpd_list_size(lst) == 1);
        REQUIRE_FALSE(cpd_atom_is_symbol(cpd_list_at(lst, 0)));
        REQUIRE_FALSE(cpd_atom_is_float(cpd_list_at(lst, 0)));
        cpd_list_free(lst);

        lst = cpd_list_new_from_string("$ 1");
        REQUIRE(cpd_list_size(lst) == 2);
        REQUIRE(cpd_atom_is_symbol(cpd_list_at(lst, 0)));
        REQUIRE(cpd_symbol_name(cpd_atom_get_symbol(cpd_list_at(lst, 0))) == std::string("$"));
        REQUIRE(cpd_atom_is_float(cpd_list_at(lst, 1)));
        cpd_list_free(lst);

        lst = cpd_list_new_from_string("$DOLLARS");
        REQUIRE(cpd_list_size(lst) == 1);
        REQUIRE(cpd_atom_is_symbol(cpd_list_at(lst, 0)));
        REQUIRE(cpd_symbol_name(cpd_atom_get_symbol(cpd_list_at(lst, 0))) == std::string("$DOLLARS"));
        cpd_list_free(lst);
    }

    SECTION("free")
    {
        auto l = cpd_list_new(4);
        REQUIRE(l);
        cpd_list_free(0);
        cpd_list_free(l);
    }

    SECTION("at")
    {
        auto l = cpd_list_new(4);
        REQUIRE(cpd_list_at(l, 0) != 0);
        REQUIRE(cpd_list_at(0, 123) == 0);
        cpd_list_free(l);
    }

    SECTION("clear")
    {
        auto l = cpd_list_new(4);
        cpd_list_clear(nullptr);
        REQUIRE(cpd_list_size(l) == 4);
        cpd_list_clear(l);
        REQUIRE(cpd_list_size(l) == 0);
        cpd_list_free(l);
    }

    SECTION("append")
    {
        auto a0 = cpd_atom_float_new(123);
        auto l = cpd_list_new(0);
        cpd_list_append(0, 0);
        cpd_list_append(l, 0);
        cpd_list_append(0, a0);
        REQUIRE(cpd_list_size(l) == 0);
        cpd_list_append(l, a0);
        REQUIRE(cpd_list_size(l) == 1);
        cpd_list_append(l, a0);
        REQUIRE(cpd_list_size(l) == 2);
        REQUIRE(cpd_atom_get_float(cpd_list_at(l, 1)) == 123);

        // null ptr
        cpd_list_append_float(0, 1.123f);
        // ok
        cpd_list_append_float(l, 1.123f);
        REQUIRE(cpd_list_get_float_at(l, 2) == 1.123f);

        // null ptr
        cpd_list_append_symbol(0, cpd_symbol("ABC"));
        // ok
        cpd_list_append_symbol(l, cpd_symbol("ABC"));
        REQUIRE(cpd_list_get_symbol_at(l, 3) == cpd_symbol("ABC"));

        cpd_list_free(l);
        cpd_atom_free(a0);
    }

    SECTION("copy")
    {
        auto a0 = cpd_atom_float_new(123);
        auto l0 = cpd_list_new(0);
        cpd_list_append(l0, a0);
        cpd_list_append(l0, a0);
        cpd_list_append(l0, a0);

        auto l1 = cpd_list_copy(l0);
        cpd_list_free(l0);
        cpd_atom_free(a0);

        REQUIRE(cpd_list_size(l1) == 3);
        REQUIRE(cpd_atom_get_float(cpd_list_at(l1, 0)) == 123);
        REQUIRE(cpd_atom_get_float(cpd_list_at(l1, 1)) == 123);
        REQUIRE(cpd_atom_get_float(cpd_list_at(l1, 2)) == 123);

        REQUIRE(cpd_list_copy(0) == 0);
    }

    SECTION("set")
    {
        auto l = cpd_list_new(0);

        REQUIRE_FALSE(cpd_list_set_atom_at(0, 0, 0));
        REQUIRE_FALSE(cpd_list_set_atom_at(l, 0, 0));
        REQUIRE_FALSE(cpd_list_set_symbol_at(0, 0, cpd_symbol("TEST")));
        REQUIRE_FALSE(cpd_list_set_symbol_at(l, 0, cpd_symbol("TEST")));
        REQUIRE_FALSE(cpd_list_set_float_at(0, 0, 1024));
        REQUIRE_FALSE(cpd_list_set_float_at(l, 0, 1024));

        auto a = cpd_atom_string_new("ABC");

        REQUIRE_FALSE(cpd_list_set_atom_at(l, 0, a));
        cpd_list_append_float(l, 123);
        REQUIRE(cpd_list_get_float_at(l, 0) == 123);
        REQUIRE(cpd_list_set_atom_at(l, 0, a));
        REQUIRE(cpd_list_set_symbol_at(l, 0, cpd_symbol("TEST")));

        cpd_list_free(l);
        cpd_atom_free(a);
    }
}
