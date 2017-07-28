#include "cpd_types.h"
#include "m_pd.h"

t_cpd_symbol* cpd_symbol_new(const char* str)
{
    return gensym(str);
}

const char* cpd_symbol_name(const t_cpd_symbol* s)
{
    return s->s_name;
}
