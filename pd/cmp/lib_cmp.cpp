#include "lib_cmp.h"

#include "m_pd.h"

extern "C" {
#include "g_canvas.h"
#include "m_imp.h"
#include "s_stuff.h"
}

#include <csignal>
#include <iostream>

extern "C" void pd_init();

int cmp_pdinit()
{
    // copied from libpd
    signal(SIGFPE, SIG_IGN);
    //    sys_soundin = NULL;
    //    sys_soundout = NULL;

    // are all these settings necessary?
    //    sys_schedblocksize = DEFDACBLKSIZE;
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
    //    sys_loaded_classes = 0;

    pd_init();
    sys_init_fdpoll();

#ifdef USEAPI_PORTAUDIO
    sys_set_audio_api(API_PORTAUDIO); // API_PORTAUDIO
#endif
#ifdef USEAPI_DUMMY
    sys_set_audio_api(API_DUMMY); // API_PORTAUDIO
#endif

    //    sys_searchpath = NULL;
    //    sys_startgui(NULL);

    if (!pd_this) {
        error("Initialization failed");
        return 0;
    } else
        std::cout << ("Pd library initialized: %x") << pd_this << "\n";

    // init audio
    int indev[MAXAUDIOINDEV], inch[MAXAUDIOINDEV],
        outdev[MAXAUDIOOUTDEV], outch[MAXAUDIOOUTDEV];

    indev[0] = outdev[0] = DEFAULTAUDIODEV;
    inch[0] = 1;
    outch[0] = 2;

    sys_set_audio_settings(1, indev, 1, inch,
        1, outdev, 1, outch, 44100, -1, 1, DEFDACBLKSIZE);
    sched_set_using_audio(SCHED_AUDIO_CALLBACK);

    sys_reopen_audio();
    return 1;
}
