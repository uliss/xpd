#include "catch.hpp"

#include "lib_cpd.h"

TEST_CASE("cpd", "[cpd PureData wrapper]")
{
    SECTION("cpd_canvas")
    {
        cpd_init();

        SECTION("predefined")
        {
            REQUIRE(cpd_root_canvas_count() == 3);
            REQUIRE(cpd_root_canvas_last() != 0);
            REQUIRE(cpd_root_canvas_at(0) != 0);
            REQUIRE(cpd_root_canvas_at(1) != 0);
            REQUIRE(cpd_root_canvas_at(2) != 0);
            REQUIRE(cpd_root_canvas_at(3) == 0);
            REQUIRE(cpd_root_canvas_at(4) == 0);
            REQUIRE(cpd_root_canvas_at(0) != cpd_root_canvas_at(1));
            REQUIRE(cpd_root_canvas_at(1) != cpd_root_canvas_at(2));
            REQUIRE(cpd_root_canvas_at(0) != cpd_root_canvas_at(2));
            REQUIRE(cpd_root_canvas_at(2) == cpd_root_canvas_last());
            REQUIRE(cpd_root_canvas_next(cpd_root_canvas_at(0)) == cpd_root_canvas_at(1));
            REQUIRE(cpd_root_canvas_next(0) == 0);

            REQUIRE(cpd_canvas_is_root(cpd_root_canvas_at(0)));
            REQUIRE(cpd_canvas_current() == 0);
        }

        SECTION("name")
        {
            REQUIRE(cpd_canvas_name(cpd_root_canvas_at(0)) == std::string("_float_array_template"));
            REQUIRE(cpd_canvas_name(cpd_root_canvas_at(1)) == std::string("_float_template"));
            REQUIRE(cpd_canvas_name(cpd_root_canvas_at(2)) == std::string("_text_template"));
        }

        SECTION("root")
        {
            REQUIRE(cpd_canvas_root(cpd_root_canvas_at(0)) == cpd_root_canvas_at(0));
            REQUIRE(cpd_canvas_root(cpd_root_canvas_at(1)) == cpd_root_canvas_at(1));
            REQUIRE(cpd_canvas_root(cpd_root_canvas_at(2)) == cpd_root_canvas_at(2));
        }

        SECTION("free")
        {
            REQUIRE(!cpd_canvas_free(0));
            REQUIRE(cpd_canvas_free(cpd_root_canvas_at(0)));
            REQUIRE(cpd_root_canvas_count() == 2);

            REQUIRE(cpd_canvas_name(cpd_root_canvas_at(0)) == std::string("_float_template"));
            REQUIRE(cpd_canvas_name(cpd_root_canvas_at(1)) == std::string("_text_template"));
        }

        SECTION("font size")
        {
            REQUIRE(cpd_canvas_fontsize(cpd_root_canvas_at(0)) == 10);
            REQUIRE(cpd_canvas_fontsize(0) == -1);
        }

        SECTION("new")
        {
            REQUIRE(cpd_canvas_current() == 0);

            size_t n = cpd_root_canvas_count();
            REQUIRE(cpd_root_canvas_new());
            REQUIRE(cpd_root_canvas_count() == n + 1);

            t_cpd_canvas* c0 = cpd_root_canvas_last();
            REQUIRE(cpd_canvas_name(cpd_root_canvas_last()) == std::string("_text_template"));
            REQUIRE(cpd_canvas_is_root(c0));

            t_cpd_canvas* c1 = cpd_root_canvas_new();
            REQUIRE(cpd_canvas_is_root(c1));
            REQUIRE(cpd_root_canvas_x(c1) == 0);
            REQUIRE(cpd_root_canvas_y(c1) == 22);
            REQUIRE(cpd_root_canvas_width(c1) == 450);
            REQUIRE(cpd_root_canvas_height(c1) == 300);
            REQUIRE(cpd_root_canvas_count() == n + 2);
            REQUIRE(c1 != 0);
            REQUIRE(c1 != c0);

            t_cpd_canvas* c2 = cpd_root_canvas_new();
            REQUIRE(cpd_canvas_is_root(c2));
            REQUIRE(cpd_root_canvas_count() == n + 3);
            REQUIRE(c2 != 0);
            REQUIRE(c2 != c1);

            cpd_canvas_free(c0);
            cpd_canvas_free(c1);
            cpd_canvas_free(c2);

            REQUIRE(cpd_root_canvas_dir(cpd_root_canvas_last()) == std::string("."));

            REQUIRE(cpd_root_canvas_count() == n);
        }
    }
}
