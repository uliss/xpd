#ifndef PdFloatArray_H
#define PdFloatArray_H

#include "object.h"

#include "pd_floatarraydata.h"
#include "canvas.h"

namespace xpd {

class PdFloatArray : public Object {
    std::string _name;
    size_t _size;

    Canvas* _parent;
    
    Observer* _observer;
public:
    PdFloatArray(const Canvas* parent, const std::string& name, size_t size);
    
    int size();
    void setSize(int size);
    
    PdFloatArrayData* getData();
    
    virtual void registerObserver(Observer* o);
    virtual void unregisterObserver(Observer* o);
};

} // namespace xpd

#endif // PdFloatArray_H
