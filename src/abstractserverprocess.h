#ifndef ABSTRACTSERVERPROCESS_H
#define ABSTRACTSERVERPROCESS_H

#include <memory>

namespace xpd {

class AbstractServerProcess {
public:
};

typedef std::shared_ptr<AbstractServerProcess> ProcessPtr;
}

#endif // ABSTRACTSERVERPROCESS_H
