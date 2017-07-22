#include "localpdprocess.h"
#include "lib_cpd.h"
#include "pdcanvas.h"

namespace xpd {

LocalPdProcess::LocalPdProcess(const AbstractServer* parent, const ServerProcessSettings& s)
    : AbstractServerProcess(parent, s)
{
    if (!cpd_init())
        throw Exception("can't start pd");
}

void LocalPdProcess::dspSwitch(bool value)
{
}

CanvasPtr LocalPdProcess::createCanvas()
{
    CanvasSettings s("Untitled-1");
    CanvasPtr cnv = std::make_shared<PdCanvas>(nullptr, s);

    if (!cnv)
        return cnv;

    canvas_list_.push_back(cnv);
    return cnv;
}

} // namespace xpd
