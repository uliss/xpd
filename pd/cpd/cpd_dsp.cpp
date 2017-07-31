#include "cpd_dsp.h"
#include "cpd_globals.h"
#include "pr_log.h"

#include "m_pd.h"

static void cpd_dsp_set_state(bool state)
{
    if (!pd_this) {
        ERROR("library not yet initialized");
        return;
    }

    t_pd* dest = CPD_SYMBOL_PD->s_thing;

    if (dest == NULL) {
        ERROR("Pd object not found");
        return;
    }

    t_atom a;
    SETFLOAT(&a, state ? 1 : 0);
    pd_typedmess(dest, gensym("dsp"), 1, &a);
}

void cpd_dsp_start()
{
    DEBUG("DSP start");
    cpd_dsp_set_state(true);
}

void cpd_dsp_stop()
{
    DEBUG("DSP stop");
    cpd_dsp_set_state(false);
}
