#ifndef SERVERCANVAS_H
#define SERVERCANVAS_H

#include <memory>
#include <string>
#include <vector>

#include "connection.h"
#include "object.h"

namespace xpd {

class CanvasObserver;
typedef std::shared_ptr<CanvasObserver> CanvasObserverPtr;
typedef std::vector<CanvasObserverPtr> CanvasObserverList;
typedef std::unique_ptr<Object> ObjectPtr;
typedef std::vector<ObjectPtr> ObjectList;
typedef std::vector<Connection> ConnectionList;

class CanvasSettings {
public:
    CanvasSettings() {}
};

class ServerCanvas {
    CanvasSettings settings_;
    std::string path_;
    CanvasObserverList observer_list_;
    ObjectList obj_list_;
    ConnectionList conn_list_;

public:
    ServerCanvas(const CanvasSettings& s);
    const CanvasSettings& settings() const;

    const std::string& path() const;
    int inletCount() const;
    int outletCount() const;

    void registerObserver(CanvasObserverPtr o);
    void deleteObserver(CanvasObserverPtr o);

    const ObjectList& objects() const;
    const ConnectionList& connections() const;

    virtual bool connect(const Object& src, int outletIdx, const Object& dest, int inletIdx);
    virtual bool disconnect(const Object& src, int outletIdx, const Object& dest, int inletIdx);
};

//    vector<ServerPatchcord*> _patchcords;
//    ServerInstance* _parentInstance;
//    void setParentInstance(ServerInstance* p) { _parentInstance = p; }
//    ServerInstance* parentInstance() { return _parentInstance; }

//    ServerObject* createObject(string name); // Object* || Canvas*
//    void deleteObject(ServerObject* o);

//    struct _glist* canvasObject();

//    ServerCanvas* createEmptySubCanvas();

//    ServerArray* createArray(string arrayName, int size);
//    void deleteArray(ServerArray* a);

//    void loadbang();

//    ServerObject* toServerObject();

} // namespace xpd

#endif // SERVERCANVAS_H
