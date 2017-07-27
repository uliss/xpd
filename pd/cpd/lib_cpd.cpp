#include "lib_cpd.h"

#include "m_pd.h"
#include "pr_log.h"

extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#include <algorithm>
#include <csignal>
#include <cstring>
#include <iostream>
#include <iterator>

extern "C" void pd_init();

static void cpd_log_print(const char* c)
{
    console()->info(c);
}

int cpd_init()
{
    static bool initialized = false;
    if (initialized) {
        console()->info("cpd_init: already initialized");
        return 1;
    }

    spdlog::set_level(spdlog::level::debug);

    // copied from libpd
    signal(SIGFPE, SIG_IGN);

    // are all these settings necessary?
    sys_externalschedlib = 0;
    sys_printtostderr = 0;
    sys_usestdpath = 0; // don't use pd_extrapath, only sys_searchpath
    sys_debuglevel = 0;
    sys_verbose = 0;
    sys_noloadbang = 0;
    sys_hipriority = 0;
    sys_nmidiin = 0;
    sys_nmidiout = 0;

    sys_printhook = 0;

    pd_init();
    sys_init_fdpoll();

    sys_set_audio_api(API_PORTAUDIO); // API_PORTAUDIO

    if (!pd_this) {
        cpd_error("Initialization failed");
        return 0;
    } else {
        console()->info("Pd library initialized: {}", static_cast<void*>(pd_this));
    }

    STUFF->st_soundin = NULL;
    STUFF->st_soundout = NULL;
    STUFF->st_schedblocksize = DEFDACBLKSIZE;
    STUFF->st_searchpath = NULL;

    // init audio
    int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
        outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];

    indev[0] = outdev[0] = DEFAULTAUDIODEV;
    inch[0] = 1;
    outch[0] = 2;

    sys_set_audio_settings(1, indev, 1, inch, 1,
        outdev, 1, outch, 44100, -1, 1, DEFDACBLKSIZE);
    sched_set_using_audio(SCHED_AUDIO_POLL);

    sys_reopen_audio();

    // hack lol - removes empty canvas with array template and creates an empty new one
    // cpd_delete_patch(cpd_new_patch(0, 0, 0, 0, 10));

    initialized = true;

    cpd_setprinthook(cpd_log_print);

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

void cpd_error(const char* msg, ...)
{
    char buf[MAXPDSTRING];
    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, MAXPDSTRING - 1, msg, ap);
    va_end(ap);
    strcat(buf, "\n");

    console()->error(buf);
    error("%s", buf);
}

void cpd_delete_patch(t_canvas* canvas)
{
    if (!canvas) {
        console()->error("cpd_closepatch: null pointer given");
        return;
    }

    canvas_free(canvas);
    console()->debug("free canvas {}", static_cast<void*>(canvas));
}

extern "C" void sys_stopgui(void);

int cpd_stop()
{
    t_canvas* x = 0;
    for (x = pd_getcanvaslist(); x; x = x->gl_next)
        canvas_vis(x, 0);

    return 1;
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

t_cpd_object* cpd_object_new(t_cpd_canvas* c, const char* name, const t_cpd_atomlist* args, int x, int y)
{
    console()->trace("cpd_object_new {");

    const size_t N = cpd_atomlist_size(args);

    std::vector<t_atom> data(N + 3);
    t_atom* argv = &data.front();

    SETFLOAT(&argv[0], x);
    SETFLOAT(&argv[1], y);
    SETSYMBOL(&argv[2], gensym(name));

    if (args) {
        auto begin = cpd_atomlist_at(const_cast<t_cpd_atomlist*>(args), 0);
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

void cpd_setprinthook(t_printhook h)
{
    sys_printhook = h;
}

void cpd_send_bang(t_cpd_object* obj)
{
    pd_typedmess(&obj->te_g.g_pd, &s_bang, 0, 0);
}

int cpd_connect(t_cpd_object* obj1, size_t outno, t_cpd_object* obj2, size_t inno)
{
    if (!obj1 || !obj2) {
        console()->error("cpd_connect: NULL objects are given");
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

void cpd_send_float(t_cpd_object* obj, float f)
{
    pd_float(&obj->te_g.g_pd, f);
}
