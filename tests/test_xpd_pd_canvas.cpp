#include "catch.hpp"

#include "abstractserver.h"
#include "abstractserverprocess.h"
#include "pd_canvas.h"
#include "pd_catcher.h"
#include "pd_localserver.h"

#include <string>

using namespace xpd;

extern const char* CATCHER_NAME;

TEST_CASE("PdCanvas", "[PdCanvas]")
{
    PdLocalServer srv(ServerSettings("local"));
    ProcessPtr p = srv.createProcess();
    CanvasPtr c = p->createCanvas();

    SECTION("init")
    {
        REQUIRE(c->type() == OBJ_TYPE_CANVAS);
    }

    SECTION("create array")
    {
        auto id0 = c->createArray("array1", 100);
        REQUIRE(id0 > 0);
        REQUIRE(c->childrenCount() == 1);
        REQUIRE(c->isRoot());
        REQUIRE(c->children().contains(id0));
        REQUIRE(c->children().findObjectIndex(id0) == 0);

        auto id1 = c->createObject("mtof", 0, 0);
        REQUIRE(c->childrenCount() == 2);
        REQUIRE(id0 < id1);
        REQUIRE(c->children().findObjectIndex(id0) == 0);
        REQUIRE(c->children().findObjectIndex(id1) == 1);

        // invalid index
        REQUIRE(c->children().findObjectIndex(-1000) == -1);
        c->removeAllChildren();
        REQUIRE(c->childrenCount() == 0);
        REQUIRE_FALSE(c->hasChildren());
    }

    SECTION("append remove")
    {
        auto sz = c->childrenCount();
        auto id0 = c->createObject("f", 0, 0);
        REQUIRE(c->childrenCount() == sz + 1);

        // invalid ID
        REQUIRE_FALSE(c->deleteObject(id0 + 1000));
        REQUIRE(c->childrenCount() == sz + 1);

        // remove
        REQUIRE(c->deleteObject(id0));
        REQUIRE(c->childrenCount() == sz);

        c->removeAllChildren();
        REQUIRE_FALSE(c->hasChildren());
    }

    SECTION("loadbang")
    {
        c->removeAllChildren();
        auto lb = c->createObject("loadbang", 0, 0);
        PdCatcher* ct = new PdCatcher(c.get());
        REQUIRE(c->connect(lb, 0, ct->id(), 0));

        REQUIRE(ct->isEmpty());
        c->loadbang();
        REQUIRE(ct->isLastBang());
    }
}
