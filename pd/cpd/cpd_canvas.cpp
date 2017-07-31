#include "cpd_canvas.h"
#include "cpd_list.h"
#include "cpd_object.h"
#include "pr_log.h"

#include "m_pd.h"
extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#define NULL_CHECK(obj)         \
    if (obj == nullptr) {       \
        DEBUG("NULL argument"); \
        return;                 \
    }

#define NULL_CHECK_RETURN(obj, ret) \
    if (obj == nullptr) {           \
        DEBUG("NULL argument");     \
        return ret;                 \
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
    NULL_CHECK_RETURN(cnv, nullptr);

    return cnv->gl_next;
}

const char* cpd_canvas_name(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return cnv->gl_name->s_name;
}

int cpd_canvas_free(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    canvas_free(cnv);
    return 1;
}

t_cpd_canvas* cpd_canvas_root(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return canvas_getrootfor(cnv);
}

int cpd_canvas_fontsize(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, -1);

    return cnv->gl_font;
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

int cpd_canvas_is_root(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_owner == 0 ? 1 : 0;
}

t_cpd_canvas* cpd_canvas_current()
{
    return canvas_getcurrent();
}

const char* cpd_root_canvas_dir(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, "");

    if (cpd_canvas_is_root(cnv) && canvas_getenv(cnv))
        return canvas_getdir(cnv)->s_name;

    DEBUG("non root canvas given");
    return "";
}

int cpd_root_canvas_x(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screenx1;
}

int cpd_root_canvas_y(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screeny1;
}

int cpd_root_canvas_width(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screenx2 - cnv->gl_screenx1;
}

int cpd_root_canvas_height(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    return cnv->gl_screeny2 - cnv->gl_screeny1;
}

size_t cpd_canvas_object_count(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, 0);

    t_gobj* l = cnv->gl_list;
    size_t n = 0;

    while (l) {
        l = l->g_next;
        n++;
    }

    return n;
}

t_cpd_object* cpd_canvas_first_object(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

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
    NULL_CHECK(cnv);

    canvas_setcurrent(cnv);
}

t_cpd_canvas* cpd_root_canvas_load(const char* name, const char* path)
{
    if (name && path) {
        t_cpd_canvas* cnv = reinterpret_cast<t_cpd_canvas*>(glob_evalfile(NULL, gensym(name), gensym(path)));

        if (cnv) {
            DEBUG("loaded \"{}/{}\"", path, name);
            return cnv;
        }

        return nullptr;
    }

    if (name) {
        t_namelist* dir_entry = STUFF->st_searchpath;

        while (dir_entry) {
            const char* rpath = dir_entry->nl_string;

            t_cpd_canvas* cnv = reinterpret_cast<t_cpd_canvas*>(glob_evalfile(NULL, gensym(name), gensym(rpath)));
            if (cnv) {
                DEBUG("loaded \"{}/{}\"", rpath, name);
                return cnv;
            }

            dir_entry = dir_entry->nl_next;
        }
    }

    return nullptr;
}

void cpd_canvas_unset_current(t_cpd_canvas* cnv)
{
    NULL_CHECK(cnv);

    canvas_unsetcurrent(cnv);
}

t_cpd_object* cpd_canvas_to_object(t_cpd_canvas* cnv)
{
    NULL_CHECK_RETURN(cnv, nullptr);

    return &cnv->gl_obj;
}

t_cpd_canvas* cpd_subpatch_new(t_cpd_canvas* parent, const char* name, t_cpd_list* args, int x, int y)
{
    NULL_CHECK_RETURN(parent, nullptr);

    bool free_arg_list = false;
    t_cpd_list* subpatch_args = 0;

    if (args) {
        // put name first
        subpatch_args = args;
        cpd_list_prepend_symbol(subpatch_args, cpd_symbol(name));
    } else {
        free_arg_list = true;
        subpatch_args = cpd_list_new(0);
        cpd_list_append_symbol(subpatch_args, cpd_symbol(name));
    }

    t_cpd_object* sub = cpd_object_new(parent, "pd", subpatch_args, x, y);
    if (!sub) {
        DEBUG("can't create subpatch");
        return nullptr;
    }

    if (free_arg_list)
        cpd_list_free(subpatch_args);

    return reinterpret_cast<t_cpd_canvas*>(sub);
}
