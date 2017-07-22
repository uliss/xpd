#ifndef SERVERCANVAS_H
#define SERVERCANVAS_H

#include <memory>
#include <string>
#include <vector>

#include "connection.h"
#include "object.h"
#include "objectlist.h"

namespace xpd {

class CanvasObserver;
typedef std::shared_ptr<CanvasObserver> CanvasObserverPtr;
typedef std::vector<CanvasObserverPtr> CanvasObserverList;

class CanvasSettings {
    std::string name_;

public:
    CanvasSettings(const std::string& name);
    const std::string& name() const;
};

class ServerCanvas : public Object {
    CanvasSettings settings_;
    std::string path_;
    CanvasObserverList observer_list_;
    ObjectList obj_list_;

public:
    ServerCanvas(const ServerCanvas* parent, const CanvasSettings& s);
    const CanvasSettings& settings() const;

    const std::string& path() const;

    void registerObserver(CanvasObserverPtr o);
    void deleteObserver(CanvasObserverPtr o);

    const ObjectList& objects() const;

    virtual bool connect(const Object& src, int outletIdx, const Object& dest, int inletIdx);
    virtual bool disconnect(const Object& src, int outletIdx, const Object& dest, int inletIdx);

    ObjectId createObject(const std::string& name);
    bool deleteObject(ObjectId objId);

    ObjectId createArray(const std::string& name, size_t size);
    bool deleteArray(const std::string& name);

    bool hasChildren() const;
    const ObjectList& children() const;
};

//    vector<ServerPatchcord*> _patchcords;
//    ServerInstance* _parentInstance;
//    void setParentInstance(ServerInstance* p) { _parentInstance = p; }
//    ServerInstance* parentInstance() { return _parentInstance; }
//    struct _glist* canvasObject();
//    ServerCanvas* createEmptySubCanvas();
//    void loadbang();
//    ServerObject* toServerObject();

} // namespace xpd

#endif // SERVERCANVAS_H
