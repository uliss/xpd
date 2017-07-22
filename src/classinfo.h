#ifndef CLASSINFO_H
#define CLASSINFO_H

#include <string>

namespace xpd {

class ClassInfo {
    std::string name_;
    std::string library_;

public:
    ClassInfo(const std::string& name);

    const std::string& name() const;
    const std::string& library() const;
};

} // namespace xpd

#endif // CLASSINFO_H
