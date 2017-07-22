#ifndef OBJECT_H
#define OBJECT_H

#include <memory>
#include <string>
#include <vector>

#include "objectproperties.h"
#include "xlets.h"

namespace xpd {

class ServerCanvas;
class Observer;
class ClassInfo;
class Object;
class ObjectList;

typedef std::unique_ptr<Object> ObjectPtr;
typedef std::vector<Inlet> InletList;
typedef std::vector<Outlet> OutletList;
typedef std::shared_ptr<Observer> ObserverPtr;
typedef std::shared_ptr<ClassInfo> ClassInfoPtr;

enum ObjectType {
    OBJ_TYPE_SIMPLE_BOX = 0,
    OBJ_TYPE_ERROR_BOX,
    OBJ_TYPE_CANVAS,
    OBJ_TYPE_ARRAY,
    OBJ_TYPE_ABSTRACTION,
    OBJ_TYPE_GUI
};

typedef size_t ObjectId;

class Object {
    std::string name_;
    const ServerCanvas* parent_;
    InletList inlet_list_;
    OutletList outlet_list_;
    ClassInfoPtr class_;
    ObjectId id_;

public:
    Object(const ServerCanvas* parent, ClassInfoPtr c, const std::string& name);
    virtual ~Object();

    const std::string& name() const;
    const ServerCanvas* parent() const;

    virtual size_t inletCount() const;
    virtual size_t outletCount() const;

    virtual ObjectType type() const;
    virtual void setType(ObjectType type);

    virtual void registerObserver(ObserverPtr o);
    virtual void deleteObserver(ObserverPtr);

    const InletList& inlets() const;
    const OutletList& outlets() const;

    virtual const ObjectProperties& properties() const;

    ObjectId id() const;

    virtual bool isRoot() const;
    virtual bool hasChildren() const;
    virtual const ObjectList& children() const;

private:
    Object(const Object&);
    void operator=(const Object&);
};

// temporary
//t_object* _pdObject;
//bool hasInternalObject() { return _pdObject != 0; }

//void message(string str);
//ServerCanvas* toServerCanvas();
//void setReceiveSymbol(string symbolName);

} // namespace xpd

#endif // OBJECT_H
