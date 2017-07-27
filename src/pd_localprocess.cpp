#include "pd_localprocess.h"
#include "lib_cpd.h"
#include "pd_canvas.h"

namespace xpd {

PdLocalProcess::PdLocalProcess(const AbstractServer* parent, const ServerProcessSettings& s)
    : AbstractServerProcess(parent, s)
{
    if (!cpd_init())
        throw Exception("can't start pd");
}

PdLocalProcess::~PdLocalProcess()
{
    cpd_stop();
}

void PdLocalProcess::dspSwitch(bool value)
{
}

CanvasPtr PdLocalProcess::createCanvas()
{
    CanvasSettings s("Untitled-1");
    CanvasPtr cnv = std::make_shared<PdCanvas>(nullptr, s);

    if (!cnv)
        return cnv;

    canvas_list_.push_back(cnv);
    return cnv;
}

} // namespace xpd
