#include "lib_cpd.h"

#include "m_pd.h"

extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#include <csignal>
#include <iostream>

#include "spdlog/spdlog.h"

extern "C" void pd_init();

// Console logger with color
static auto console = spdlog::stdout_color_mt("cpd");

int cpd_init()
{
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
        console->info("Pd library initialized: {}", static_cast<void*>(pd_this));
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
    return 1;
}

t_canvas* cpd_new_patch(int x, int y, int w, int h, int font_size)
{
    t_atom argv[5];
    SETFLOAT(&argv[0], x);
    SETFLOAT(&argv[1], y);
    SETFLOAT(&argv[2], w);
    SETFLOAT(&argv[3], h);
    SETFLOAT(&argv[4], font_size);

    pd_typedmess(&pd_canvasmaker, gensym("canvas"), 5, argv);
    t_canvas* ret = (t_canvas*)pd_newest();

    console->debug("new canvas ({},{} {}x{}) with font size {}. {}",
        x, y, w, h, font_size, static_cast<void*>(ret));

    return ret;
}

void cpd_error(const char* msg, ...)
{
    char buf[MAXPDSTRING];
    va_list ap;
    va_start(ap, msg);
    vsnprintf(buf, MAXPDSTRING - 1, msg, ap);
    va_end(ap);
    strcat(buf, "\n");

    console->error(buf);
    error("%s", buf);
}
