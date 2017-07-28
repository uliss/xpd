#include "cpd_canvas.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

t_cpd_canvas* cpd_root_canvas_last()
{
    t_cpd_canvas* cnv = pd_getcanvaslist();

    if (!cnv)
        return cnv;

    while (cnv->gl_next) {
        cnv = cnv->gl_next;
    }

    return cnv;
}

size_t cpd_root_canvas_count()
{
    t_cpd_canvas* cnv = pd_getcanvaslist();

    size_t n = 0;

    while (cnv) {
        cnv = cnv->gl_next;
        n++;
    }

    return n;
}

t_cpd_canvas* cpd_root_canvas_at(size_t n)
{
    t_cpd_canvas* cnv = pd_getcanvaslist();

    size_t cur = 0;

    while (cnv) {
        if (cur == n)
            return cnv;

        cnv = cnv->gl_next;
        cur++;
    }

    return 0;
}

t_cpd_canvas* cpd_root_canvas_next(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_root_canvas_next: NULL given");
        return cnv;
    }

    return cnv->gl_next;
}

const char* cpd_canvas_name(t_cpd_canvas* c)
{
    if (!c) {
        console()->debug("cpd_canvas_name: NULL given");
        return 0;
    }

    return c->gl_name->s_name;
}

int cpd_canvas_free(t_cpd_canvas* c)
{
    if (!c) {
        console()->debug("cpd_canvas_free: NULL given");
        return 0;
    }

    canvas_free(c);
    return 1;
}

t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* c)
{
    if (!c) {
        console()->debug("cpd_canvas_root: NULL given");
        return 0;
    }

    return canvas_getrootfor(c);
}

int cpd_canvas_fontsize(t_cpd_canvas* c)
{
    if (!c) {
        console()->debug("cpd_canvas_fontsize: NULL given");
        return -1;
    }

    return c->gl_font;
}

t_cpd_canvas* cpd_root_canvas_new()
{
    static int cnt = 1;
    fmt::MemoryWriter w;
    w.write("Untitled-{}", cnt++);

    if (canvas_getcurrent())
        canvas_unsetcurrent(canvas_getcurrent());

    glob_setfilename(0, gensym(w.c_str()), gensym("~/"));
    t_cpd_canvas* res = canvas_new(0, 0, 0, 0);
    return res;
}

int cpd_canvas_is_root(t_cpd_canvas* c)
{
    if (!c) {
        console()->debug("cpd_canvas_is_root: NULL given");
        return 0;
    }

    return c->gl_owner == 0 ? 1 : 0;
}

t_cpd_canvas* cpd_canvas_current()
{
    return canvas_getcurrent();
}

const char* cpd_root_canvas_dir(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_root_canvas_dir: NULL given");
        return "";
    }

    if (cpd_canvas_is_root(cnv) && canvas_getenv(cnv))
        return canvas_getdir(cnv)->s_name;

    console()->debug("cpd_root_canvas_dir: non root canvas given");
    return "";
}

int cpd_root_canvas_x(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_root_canvas_x: NULL given");
        return 0;
    }

    return cnv->gl_screenx1;
}

int cpd_root_canvas_y(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_root_canvas_y: NULL given");
        return 0;
    }

    return cnv->gl_screeny1;
}

int cpd_root_canvas_width(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_root_canvas_width: NULL given");
        return 0;
    }

    return cnv->gl_screenx2 - cnv->gl_screenx1;
}

int cpd_root_canvas_height(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_root_canvas_height: NULL given");
        return 0;
    }

    return cnv->gl_screeny2 - cnv->gl_screeny1;
}

size_t cpd_canvas_object_count(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_canvas_object_count: NULL given");
        return 0;
    }

    t_gobj* l = cnv->gl_list;
    size_t n = 0;

    while (l) {
        l = l->g_next;
        n++;
    }

    return n;
}

t_cpd_object* cpd_canvas_object_first(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_canvas_object_first: NULL given");
        return 0;
    }

    t_gobj* l = cnv->gl_list;
    while (l) {
        if (l->g_pd->c_patchable)
            return reinterpret_cast<t_cpd_object*>(l);

        l = l->g_next;
    }

    return nullptr;
}

void cpd_canvas_set_current(t_cpd_canvas* cnv)
{
    if (!cnv) {
        console()->debug("cpd_canvas_set_current: NULL given");
        return;
    }

    canvas_setcurrent(cnv);
}
