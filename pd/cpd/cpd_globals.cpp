#include "cpd_globals.h"

#include "m_pd.h"

t_cpd_symbol* CPD_SYMBOL_PD = 0;
t_cpd_symbol* CPD_SYMBOL_OBJ = 0;

void cpd_globals_init()
{
    CPD_SYMBOL_PD = gensym("pd");
    CPD_SYMBOL_OBJ = gensym("obj");
}
