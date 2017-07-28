#include "cpd_object.h"
#include "cpd.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, const t_cpd_list* args, int x, int y)
{
    console()->trace("cpd_object_new {");

    const size_t N = cpd_list_size(args);

    std::vector<t_atom> data(N + 3);
    t_atom* argv = &data.front();

    SETFLOAT(&argv[0], x);
    SETFLOAT(&argv[1], y);
    SETSYMBOL(&argv[2], gensym(name));

    if (args) {
        auto begin = cpd_list_at(const_cast<t_cpd_list*>(args), 0);
        std::copy(begin, begin + N, argv + 3);
    }

    pd_typedmess((t_pd*)c, gensym("obj"), N + 3, argv);

    t_pd* ptr = pd_newest();
    if (!ptr) {
        cpd_error("cpd_object_new: object creation failed");
        return 0;
    }

    t_object* res = pd_checkobject(ptr);
    if (!res) {
        cpd_error("cpd_object_new: invalid object");
        return 0;
    }

    console()->debug("  cpd_object_new: created [{}] ({})", name, (void*)res);
    return res;
}

void cpd_object_free(t_cpd_canvas* cnv, t_cpd_object* obj)
{
    if (!cnv) {
        console()->error("cpd_object_free: NULL canvas given");
        return;
    }

    if (!obj) {
        console()->error("cpd_object_free: NULL object given");
        return;
    }

    console()->debug("  cpd_object_free: [{}]", cpd_object_name(obj));

    glist_delete(cnv, &obj->te_g);
}

const char* cpd_object_name(t_cpd_object* obj)
{
    if (!obj)
        return "";

    return obj->te_g.g_pd->c_name->s_name;
}

t_cpd_list* cpd_object_arguments(t_cpd_object* obj)
{
    if (!obj) {
        console()->error("cpd_object_text: NULL pointer given");
        return 0;
    }

    t_binbuf* b = ((t_text*)(obj))->te_binbuf;
    const t_atom* atoms = binbuf_getvec(b);
    const size_t N = binbuf_getnatom(b);
    t_cpd_list* res = cpd_list_new(N - 1);

    for (size_t i = 1; i < N; i++) {
        cpd_atom_set_atom(cpd_list_at(res, i), &atoms[i]);
    }

    return res;
}

const char* cpd_object_text(t_cpd_object* obj)
{
    if (!obj) {
        console()->error("cpd_object_text: NULL pointer given");
        return "";
    }

    int size = 0;
    char* txt = 0;

    binbuf_gettext(((t_text*)(obj))->te_binbuf, &txt, &size);
    const char* res = strdup(txt);
    t_freebytes(txt, size);

    return res;
}

int cpd_object_xpos(t_cpd_object* obj)
{
    if (!obj)
        return -1;

    return obj->te_xpix;
}

int cpd_object_ypos(t_cpd_object* obj)
{
    if (!obj)
        return -1;

    return obj->te_ypix;
}

void cpd_object_set_xpos(t_cpd_object* obj, int x)
{
    if (!obj)
        return;

    obj->te_xpix = x;
}

void cpd_object_set_ypos(t_cpd_object* obj, int y)
{
    if (!obj)
        return;

    obj->te_ypix = y;
}

size_t cpd_object_inlet_count(t_cpd_object* obj)
{
    if (!obj)
        return 0;

    return obj_ninlets(obj);
}

size_t cpd_object_outlet_count(t_cpd_object* obj)
{
    if (!obj)
        return 0;

    return obj_noutlets(obj);
}

int cpd_connect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno)
{
    if (!obj1 || !obj2) {
        console()->error("cpd_connect: NULL objects are given");
        return 0;
    }

    if (obj1 == obj2) {
        console()->error("cpd_connect: self-connection");
        return 0;
    }

    if (outno >= cpd_object_outlet_count(obj1)) {
        console()->error("cpd_connect: invalid source outlet {}", outno);
        return 0;
    }

    if (inno >= cpd_object_inlet_count(obj2)) {
        console()->error("cpd_connect: invalid destination inlet {}", inno);
        return 0;
    }

    auto conn = obj_connect(obj1, outno, obj2, inno);
    return 1;
}

int cpd_is_canvas(t_cpd_object* x)
{
    if (!x) {
        console()->error("cpd_is_canvas: null pointer given");
        return 0;
    }

    return (pd_class(&x->te_pd) == canvas_class);
}

void cpd_send_bang(t_cpd_object* obj)
{
    if (!obj) {
        console()->error("cpd_send_bang: NULL pointer given");
        return;
    }

    pd_bang(&obj->te_g.g_pd);
}

void cpd_send_float(t_cpd_object* obj, t_cpd_float f)
{
    if (!obj) {
        console()->error("cpd_send_float: NULL pointer given");
        return;
    }

    pd_float(&obj->te_g.g_pd, f);
}

void cpd_send_symbol(t_cpd_object* obj, t_cpd_symbol* s)
{
    if (!obj || !s) {
        console()->error("cpd_send_symbol: NULL pointer given");
        return;
    }

    pd_symbol(&obj->te_g.g_pd, s);
}

void cpd_send_list(t_cpd_object* obj, const t_cpd_list* l)
{
    if (!obj || !l) {
        console()->error("cpd_send_list: NULL pointer given");
        return;
    }

    int n = cpd_list_size(l);
    t_cpd_atom* atoms = cpd_list_at(const_cast<t_cpd_list*>(l), 0);

    pd_list(&obj->te_g.g_pd, &s_list, n, atoms);
}

void cpd_send_message(t_cpd_object* obj, t_cpd_symbol* sel, const t_cpd_list* l)
{
    if (!obj || !sel) {
        console()->error("cpd_send_message: NULL pointer given");
        return;
    }

    int n = cpd_list_size(l);
    t_cpd_atom* atoms = cpd_list_at(const_cast<t_cpd_list*>(l), 0);

    pd_typedmess(&obj->te_g.g_pd, sel, n, atoms);
}
