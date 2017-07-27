#ifndef PD_ARGUMENTS_H
#define PD_ARGUMENTS_H

#include "arguments.h"
#include "lib_cpd.h"

namespace xpd {

class PdArguments : public Arguments {
    t_cpd_atomlist* lst_;

public:
    PdArguments();
    PdArguments(const PdArguments&);
    explicit PdArguments(float v);
    explicit PdArguments(const std::string& s);
    ~PdArguments();

    void operator=(const PdArguments&);

    void parseString(const std::string& s);

    void clear();
};

} // namespace xpd

#endif // PD_ARGUMENTS_H
