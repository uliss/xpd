#ifndef SERVERCANVAS_H
#define SERVERCANVAS_H

namespace xpd {

class CanvasSettings {
public:
    CanvasSettings() {}
};

class ServerCanvas {
    CanvasSettings settings_;

public:
    ServerCanvas(const CanvasSettings& s);
    const CanvasSettings& settings() const;
};

} // namespace xpd

#endif // SERVERCANVAS_H
