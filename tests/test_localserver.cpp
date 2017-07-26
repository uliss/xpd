#include "catch.hpp"

#include "abstractserverprocess.h"
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

        ProcessPtr p0 = srv.createProcess();
        REQUIRE(p0);
        REQUIRE(srv.processList().size() == 1);

        ProcessPtr p1 = srv.createProcess();
        REQUIRE(p0);
        REQUIRE(p0 == p1);
        REQUIRE(srv.processList().size() == 1);

        REQUIRE(p1->parent() == p0->parent());
        REQUIRE(p1->parent() == &srv);

        // create new canvas
        REQUIRE(p0->canvasCount() == 0);
        CanvasPtr cnv0 = p0->createCanvas();

        REQUIRE(cnv0);
        REQUIRE(p0->canvasCount() == 1);
        REQUIRE(p0->canvasList().size() == 1);
    }

    SECTION("c2")
    {
        LocalPdServer srv(ServerSettings("local"));

        {
            ProcessPtr p = srv.createProcess();
            CanvasPtr cnv = p->createCanvas();
            REQUIRE(p->canvasCount() == 1);
            REQUIRE(!p->deleteCanvas(CanvasPtr()));
            REQUIRE(p->canvasCount() == 1);
            REQUIRE(p->deleteCanvas(cnv));
            REQUIRE(p->canvasCount() == 0);
        }

        {
            ProcessPtr p = srv.createProcess();
            CanvasPtr cnv = p->createCanvas();
            REQUIRE(p->canvasCount() == 1);
        }
    }
}
