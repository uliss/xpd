#include "catch.hpp"

#include "abstractserverprocess.h"
#include "canvas.h"
#include "pd_canvas.h"
#include "pd_floatarray.h"
#include "pd_localserver.h"
#include "pd_object.h"

#include <memory>
#include <string>

using namespace xpd;

TEST_CASE("PdFloatArray", "[PdFloatArray]")
{
    PdLocalServer srv(ServerSettings("local"));
    ProcessPtr p = srv.createProcess();
    CanvasPtr c = p->createCanvas();

    SECTION("init")
    {
        PdFloatArray arr(c.get(), "array1", 10);
        REQUIRE(arr.size() == 10);
        REQUIRE_FALSE(arr.empty());
        REQUIRE(arr.name() == "array1");
        REQUIRE(arr.at(0) == 0.f);
        REQUIRE(arr.at(9) == 0.f);
        REQUIRE_THROWS_AS(arr.at(10), FloatArray::Exception);
    }

    SECTION("resize")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        REQUIRE(arr.resize(5));
        REQUIRE_FALSE(arr.resize(0));
    }
}
