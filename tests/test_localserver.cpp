#include "catch.hpp"

#include "localserver.h"
using namespace xpd;

TEST_CASE("localserver", "[server]")
{
    SECTION("init")
    {
        ServerSettings s("local pd");
        LocalPdServer srv(s);

        REQUIRE(srv.name() == "local pd");
        REQUIRE(srv.processList().empty());

        ServerSettings s1("other pd");
        srv.setSettings(s1);
        REQUIRE(srv.settings() == s1);
        REQUIRE(srv.settings() != s);

        REQUIRE(srv.name() == "other pd");
    }

    SECTION("create")
    {
        LocalPdServer srv(ServerSettings("local"));

        ProcessPtr p = srv.createProcess();
        REQUIRE(p);
        REQUIRE(srv.processList().size() == 1);

        ProcessPtr p1 = srv.createProcess();
        REQUIRE(p);
        REQUIRE(p == p1);
        REQUIRE(srv.processList().size() == 1);
    }
}
