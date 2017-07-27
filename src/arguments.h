#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include <mapbox/variant.hpp>
#include <string>
#include <vector>

namespace xpd {

typedef mapbox::util::variant<float, std::string> Arg;
typedef std::vector<Arg> ArgList;

class Arguments {
protected:
    ArgList args_;

public:
    Arguments();
    explicit Arguments(float v);
    explicit Arguments(const std::string& s);
    virtual ~Arguments();

    const ArgList& args() const;
    ArgList& args();

    void add(float f);
    void add(const std::string& s);

    virtual void parseString(const std::string& s);
    
    virtual void clear();
};

} // namespace xpd

#endif // ARGUMENTS_H
