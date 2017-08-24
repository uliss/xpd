#include "cpd_loader.h"
#include "pr_log.h"

#include "m_pd.h"
#include "m_imp.h"
#include "g_canvas.h"
#include "s_stuff.h"

int cpd_load_library(t_cpd_symbol* s)
{
    return sys_load_lib(canvas_getcurrent(), s->s_name);
}

