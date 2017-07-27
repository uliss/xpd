#include "catch.hpp"

#include "abstractserverprocess.h"
#include "canvas.h"

using namespace xpd;

class TestObject : public Object {
public:
    TestObject(const std::string& name)
        : Object(0, name)
    {
        cnt++;
    }

    ~TestObject()
    {
        cnt--;
    }

public:
    static int cnt;
};

int TestObject::cnt = 0;

TEST_CASE("ObjectList", "[server]")
{
    SECTION("init")
    {
        ObjectList lst;
        REQUIRE(lst.empty());
        REQUIRE(lst.size() == 0);
        REQUIRE(lst.connections().empty());
        REQUIRE(lst.size() == 0);
    }

    SECTION("append")
    {
        ObjectList lst;
        REQUIRE_FALSE(lst.append(0));

        REQUIRE(lst.size() == 0);

        REQUIRE(lst.append(new TestObject("test")));
        REQUIRE(lst.append(new TestObject("test")));

        REQUIRE(lst.size() == 2);

        auto o = new TestObject("test2");
        REQUIRE(lst.append(o));
        REQUIRE(lst.findObject(o->id()));
        REQUIRE(lst.contains(o->id()));

        // double insertion
        REQUIRE_FALSE(lst.append(o));
    }

    REQUIRE(TestObject::cnt == 0);
}
