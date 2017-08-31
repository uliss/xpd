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

    virtual bool connect(ObjectId, size_t outletIdx, ObjectId dest, size_t inletIdx);
    virtual bool disconnect(ObjectId src, size_t outletIdx, ObjectId dest, size_t inletIdx);

    virtual ObjectId createObject(const std::string& name, int x, int y) = 0;
    virtual bool deleteObject(ObjectId objId);

    /**
     * Creates new array and appends it to child list
     * @param name - array name
     * @param size - array size
     * @return array ID
     */
    virtual ObjectId createArray(const std::string& name, size_t size) = 0;

    bool hasChildren() const;
    size_t childrenCount() const;
    const ObjectList& children() const;
    void removeAllChildren();

    ObjectType type() const;

    void sendBang(ObjectId id);
    void sendFloat(ObjectId id, float f);

    /**
     * Sends loadbang to all objects
     */
    virtual void loadbang();

    /**
     * If canvas has no parents - it's root canvas
     */
    bool isRoot() const;

    virtual std::vector<std::string> availableObjects() const;
};

//    vector<ServerPatchcord*> _patchcords;
//    ServerInstance* _parentInstance;
//    struct _glist* canvasObject();
//    ServerCanvas* createEmptySubCanvas();
//    ServerObject* toServerObject();

} // namespace xpd

#endif // SERVERCANVAS_H
