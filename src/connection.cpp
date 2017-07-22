#include "connection.h"

using namespace xpd;

Connection::Connection(const Object& src, int outln, const Object& dest, int inln)
    : src_(src.id())
    , dest_(dest.id())
    , src_out_(outln)
    , dest_in_(inln)
{
}
