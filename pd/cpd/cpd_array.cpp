#include "cpd_array.h"
#include "cpd_globals.h"
#include "cpd_types.h"

#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"

t_scalar* garray_getscalar(t_garray* x);
}

#include <algorithm>

static t_symbol* SYM_TEMPLATE_ARRAY = gensym("pd-float-array");
static t_symbol* SYM_ARRAY_LINEWIDTH = gensym("linewidth");

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

t_cpd_array* cpd_array_new(t_cpd_canvas* c, t_cpd_symbol* name, size_t size, int flags)
{
    if (!c) {
        DEBUG("NULL canvas cpointer given");
        return nullptr;
    }

    size = std::max<size_t>(1, size);

    auto arr = graph_array(c, name, &s_float, size, flags);
    canvas_dirty(c, 1);
    return arr;

    //    template_setfloat(template, gensym("style"), x->x_scalar->sc_vec,
    //        style, 1);
    //    template_setfloat(template, gensym("linewidth"), x->x_scalar->sc_vec,
    //        ((style == PLOTSTYLE_POINTS) ? 2 : 1), 1);
}

size_t cpd_array_size(t_cpd_array* a)
{
    if (!a) {
        DEBUG("NULL argument");
        return 0;
    }

    t_array* arr = garray_getarray(a);
    if (!arr) {
        DEBUG("Invalid array pointer");
        return 0;
    }

    return arr->a_n;
}

void cpd_array_free(t_cpd_canvas* c, t_cpd_array* arr)
{
    if (!c) {
        ERROR("NULL canvas given");
        return;
    }

    if (!arr) {
        ERROR("NULL array given");
        return;
    }

    glist_delete(c, reinterpret_cast<t_gobj*>(arr));
}

float cpd_array_linewidth(t_cpd_array* arr)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return 0;
    }

    auto tmpl = template_findbyname(SYM_TEMPLATE_ARRAY);
    if (!tmpl) {
        DEBUG("couldn't find template {}", SYM_TEMPLATE_ARRAY->s_name);
        return 0;
    }

    auto scalar = garray_getscalar(arr);
    return template_getfloat(tmpl, SYM_ARRAY_LINEWIDTH, scalar->sc_vec, 1);
}

int cpd_array_set_linewidth(t_cpd_array* arr, float wd)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return 0;
    }

    auto tmpl = template_findbyname(SYM_TEMPLATE_ARRAY);
    if (!tmpl) {
        DEBUG("couldn't find template {}", SYM_TEMPLATE_ARRAY->s_name);
        return 0;
    }

    auto scalar = garray_getscalar(arr);
    template_setfloat(tmpl, SYM_ARRAY_LINEWIDTH, scalar->sc_vec, wd, 1);
    return 1;
}
