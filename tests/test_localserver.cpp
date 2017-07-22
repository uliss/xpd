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
        REQUIRE(s1 == srv.settings());
    }
}
