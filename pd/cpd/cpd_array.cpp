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
int garray_getname(t_garray* x, t_symbol** namep);
}

#include <algorithm>

static t_symbol* SYM_TEMPLATE_ARRAY = gensym("pd-float-array");
static t_symbol* SYM_ARRAY_LINEWIDTH = gensym("linewidth");
static t_symbol* SYM_ARRAY_STYLE = gensym("style");

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

t_cpd_float cpd_array_float_field(t_cpd_array* arr, t_cpd_symbol* name)
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
    return template_getfloat(tmpl, name, scalar->sc_vec, 1);
}

int cpd_array_set_float_field(t_cpd_array* arr, t_cpd_symbol* name, t_cpd_float val)
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
    template_setfloat(tmpl, name, scalar->sc_vec, val, 1);
    return 1;
}

t_cpd_float cpd_array_linewidth(t_cpd_array* arr)
{
    return cpd_array_float_field(arr, SYM_ARRAY_LINEWIDTH);
}

int cpd_array_set_linewidth(t_cpd_array* arr, t_cpd_float wd)
{
    return cpd_array_set_float_field(arr, SYM_ARRAY_LINEWIDTH, wd);
}

t_cpd_array_flags cpd_array_plotstyle(t_cpd_array* arr)
{
    int val = cpd_array_float_field(arr, SYM_ARRAY_STYLE);
    // see fuzzy flag logic in g_array.c: graph_array
    switch (val) {
    case 0:
        return CPD_ARRAY_STYLE_POLY;
    case 1:
        return CPD_ARRAY_STYLE_POINTS;
    case 2:
        return CPD_ARRAY_STYLE_BEZIER;
    default: {
        DEBUG("unknown array plot style: {}", val);
        return CPD_ARRAY_STYLE_POINTS;
    }
    }
}

int cpd_array_set_plotstyle(t_cpd_array* arr, t_cpd_array_flags style)
{
    int flag = 0;
    switch (style) {
    case CPD_ARRAY_STYLE_POLY:
        flag = 0;
        break;
    case CPD_ARRAY_STYLE_POINTS:
        flag = 1;
        break;
    case CPD_ARRAY_STYLE_BEZIER:
        flag = 2;
        break;
    default:
        DEBUG("unknown style flag: {}", style);
        return 0;
    }

    return cpd_array_set_float_field(arr, SYM_ARRAY_STYLE, flag);
}

int cpd_array_hidden_name(t_cpd_array* arr)
{
    if (!arr) {
        DEBUG("NULL array pointer given");
        return 0;
    }

    t_symbol* foo;
    return garray_getname(arr, &foo) ? 1 : 0;
}

t_cpd_array* cpd_array_find_by_name(t_cpd_symbol* name)
{
    return reinterpret_cast<t_cpd_array*>(pd_findbyclass(name, garray_class));
}
