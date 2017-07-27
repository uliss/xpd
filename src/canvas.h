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
    int x_, y_;
    size_t w_, h_;

public:
    CanvasSettings(const std::string& name, int x = 0, int y = 0, size_t w = 600, size_t h = 400);
    const std::string& name() const;

    int x() const { return x_; }
    int y() const { return y_; }
    size_t width() const { return w_; }
    size_t height() const { return h_; }
};

class Canvas : public Object {
protected:
    CanvasSettings settings_;
    std::string path_;
    CanvasObserverList observer_list_;
    ObjectList obj_list_;

public:
    Canvas(const Canvas* parent, const CanvasSettings& s);
    const CanvasSettings& settings() const;

    const std::string& path() const;

    void registerObserver(CanvasObserverPtr o);
    void deleteObserver(CanvasObserverPtr o);

    const ObjectList& objects() const;

    virtual bool connect(ObjectId, int outletIdx, ObjectId dest, int inletIdx);
    virtual bool disconnect(ObjectId src, int outletIdx, ObjectId dest, int inletIdx);

    virtual ObjectId createObject(const std::string& name, int x, int y) = 0;
    virtual bool deleteObject(ObjectId objId);

    ObjectId createArray(const std::string& name, size_t size);
    bool deleteArray(const std::string& name);

    bool hasChildren() const;
    size_t childrenCount() const;
    const ObjectList& children() const;

    ObjectType type() const;
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
