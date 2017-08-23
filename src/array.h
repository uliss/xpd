#ifndef ARRAY_H
#define ARRAY_H

#include "object.h"

#include "arraydata.h"
#include "canvas.h"

namespace xpd {

class Array : public Object {
    std::string _name;
    size_t _size;

    Canvas* _parent;
    
    Observer* _observer;
public:
    Array(const Canvas* parent, const std::string& name, size_t size);
    
    int size();
    void setSize(int size);
    
    ArrayData* getData();
    
    virtual void registerObserver(Observer* o);
    virtual void unregisterObserver(Observer* o);
};

} // namespace xpd

#endif // ARRAY_H
