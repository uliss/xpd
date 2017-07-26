#ifndef PDOBJECT_H
#define PDOBJECT_H

#include "lib_cpd.h"
#include "object.h"

namespace xpd {

class PdObject : public Object {
    t_cpd_canvas* cnv_;
    t_cpd_object* obj_;

public:
    PdObject(const Canvas* parent, const std::string& name, int x = 0, int y = 0);
    ~PdObject();
};

} // namespace xpd

#endif // PDOBJECT_H
