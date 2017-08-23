#include "cpd_array.h"
#include "cpd_types.h"

#include "pr_log.h"

#include "m_pd.h"
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"

t_cpd_array* cpd_get_array(t_cpd_symbol* arrayname)
{
    t_cpd_array* ret = (t_cpd_array*)pd_findbyclass(arrayname, garray_class);
    return ret;
}

// variant 1 - yet disabled
//void cpd_get_array_data(t_cpd_array* a, int* size, float** vec)
//{
//    // needs fix for t_word
//    garray_getfloatwords(a, size, (t_word**)vec);
//}

float* cpd_get_array_data(t_cpd_array* a)
{
    return (float*)garray_vec(a);
}

int cpd_get_array_size(t_cpd_array* a)
{
    return garray_npoints(a);
}

t_cpd_array* cpd_new_array(t_cpd_canvas* c, t_cpd_symbol* name, t_cpd_float size, t_cpd_float save, t_cpd_float newgraph)
{
    //possibly unused as we use arrays by symbol lookup table
    t_garray* ret;
    glist_arraydialog(c, name, size, save, newgraph);
    ret = cpd_get_array(name);
    return ret;
}
