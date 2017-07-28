#include "cpd.h"

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

extern "C" void sys_stopgui(void);

int cpd_stop()
{
    t_canvas* x = 0;
    for (x = pd_getcanvaslist(); x; x = x->gl_next)
        canvas_vis(x, 0);

    return 1;
}

void cpd_setprinthook(t_printhook h)
{
    sys_printhook = h;
}
