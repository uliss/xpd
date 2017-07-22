#ifndef CONNECTION_H
#define CONNECTION_H

#include <memory>

#include "object.h"

namespace xpd {

class Canvas;

class Connection {
    ObjectId src_, dest_;
    int src_out_, dest_in_;

public:
    Connection(const Object& src, int outln, const Object& dest, int inln);

    ObjectId src() const { return src_; }
    ObjectId dest() const { return dest_; }
};

} // namespace xpm

#endif // CONNECTION_H
