#include "catch.hpp"

#include "abstractserverprocess.h"
#include "localserver.h"
#include "pdobject.h"
#include "servercanvas.h"

using namespace xpd;

TEST_CASE("PdObject", "[server]")
{
    LocalPdServer srv(ServerSettings("local"));
    ProcessPtr p = srv.createProcess();
    CanvasPtr c = p->createCanvas();

    SECTION("init")
    {
        REQUIRE(c->type() == OBJ_TYPE_CANVAS);

        auto o = std::make_shared<PdObject>(c.get(), "mtof", PdArguments(), 100, 200);
        REQUIRE(o->x() == 100);
        REQUIRE(o->y() == 200);

        REQUIRE(o->inletCount() == 1);
        REQUIRE(o->outletCount() == 1);

        o = std::make_shared<PdObject>(c.get(), "metro", PdArguments(), 10, 20);
        REQUIRE(o->x() == 10);
        REQUIRE(o->y() == 20);

        REQUIRE(o->inletCount() == 2);
        REQUIRE(o->outletCount() == 1);

        REQUIRE_FALSE(o->isRoot());
        REQUIRE_FALSE(o->hasChildren());
        REQUIRE(o->children().empty());
        REQUIRE(o->type() == OBJ_TYPE_SIMPLE_BOX);
    }

    SECTION("inlet count")
    {
        auto o = std::make_shared<PdObject>(c.get(), "metro");
        REQUIRE(o->inletCount() == 2);
        REQUIRE(o->outletCount() == 1);
    }
}
