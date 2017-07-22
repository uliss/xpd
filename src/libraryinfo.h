#ifndef LIBRARYINFO_H
#define LIBRARYINFO_H

#include <string>

namespace xpd {

class LibraryInfo {
    std::string name_;
    std::string version_;

public:
    LibraryInfo(const std::string& name);
    const std::string& name() const;
    const std::string& version() const;
};

} // namespace xpd

#endif // LIBRARYINFO_H
