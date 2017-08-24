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
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_LINES);

        REQUIRE(arr.at(0) == 0.f);
        REQUIRE(arr.at(9) == 0.f);
        REQUIRE_THROWS_AS(arr.at(10), FloatArray::Exception);

        REQUIRE_THROWS_AS(PdFloatArray(nullptr, "array2", 1000), FloatArray::Exception);
    }

    SECTION("resize")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        REQUIRE(arr.resize(5));
        REQUIRE_FALSE(arr.resize(0));
    }

    SECTION("plotStyle")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        REQUIRE(arr.plotStyle() == FloatArray::PLOT_LINES);
        arr.setPlotStyle(FloatArray::PLOT_POINTS);
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_POINTS);
        arr.setPlotStyle(FloatArray::PLOT_BEZIER);
        REQUIRE(arr.plotStyle() == FloatArray::PLOT_BEZIER);
    }

    SECTION("fill")
    {
        PdFloatArray arr(c.get(), "array1", 10);

        arr.fill(1000);
        REQUIRE(arr.at(0) == 1000.f);
        REQUIRE(arr.at(1) == 1000.f);
        REQUIRE(arr.at(9) == 1000.f);

        REQUIRE(arr.resize(5));
        arr.fill(2000);
        REQUIRE(arr.at(0) == 2000.f);
        REQUIRE(arr.at(4) == 2000.f);
    }
}
