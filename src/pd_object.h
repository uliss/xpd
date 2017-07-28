#ifndef PDOBJECT_H
#define PDOBJECT_H

#include "object.h"
#include "pd_arguments.h"

#include "cpd/cpd_canvas.h"

namespace xpd {

class PdObject : public Object {
    t_cpd_canvas* cnv_;
    t_cpd_object* obj_;
    size_t inlet_n_;
    size_t outlet_n_;
    PdArguments args_;

public:
    PdObject(const Canvas* parent, const std::string& name, const PdArguments& args = PdArguments(), int x = 0, int y = 0);
    ~PdObject();

    void setX(int x);
    void setY(int y);

    size_t inletCount() const;
    size_t outletCount() const;

    const Arguments& arguments() const;

    t_cpd_object* pdObject();

    void sendBang();
    void sendFloat(float f);
    void sendSymbol(const std::string& s);
};

} // namespace xpd

#endif // PDOBJECT_H
