set(PD_SOURCES
    pure-data/src/d_arithmetic.c
    pure-data/src/d_array.c
    pure-data/src/d_ctl.c
    pure-data/src/d_dac.c
    pure-data/src/d_delay.c
    pure-data/src/d_fft.c
    pure-data/src/d_fft_fftsg.c
    pure-data/src/d_filter.c
    pure-data/src/d_global.c
    pure-data/src/d_math.c
    pure-data/src/d_misc.c
    pure-data/src/d_osc.c
    pure-data/src/d_resample.c
    pure-data/src/d_soundfile.c
    pure-data/src/d_ugen.c
    pure-data/src/g_all_guis.c
    pure-data/src/g_all_guis.h
    pure-data/src/g_array.c
    pure-data/src/g_canvas.c
    pure-data/src/g_canvas.h
    pure-data/src/g_clone.c
    pure-data/src/g_editor.c
    pure-data/src/g_graph.c
    pure-data/src/g_guiconnect.c
    pure-data/src/g_io.c
    pure-data/src/g_mycanvas.c
    pure-data/src/g_readwrite.c
    pure-data/src/g_rtext.c
    pure-data/src/g_scalar.c
    pure-data/src/g_template.c
    pure-data/src/g_text.c
    pure-data/src/g_traversal.c
    pure-data/src/m_atom.c
    pure-data/src/m_binbuf.c
    pure-data/src/m_class.c
    mocks/m_conf.c
    pure-data/src/m_glob.c
    pure-data/src/m_imp.h
    pure-data/src/m_memory.c
    pure-data/src/m_obj.c
    pure-data/src/m_pd.c
    pure-data/src/m_pd.h
    pure-data/src/m_sched.c
    pure-data/src/s_audio.c
    pure-data/src/s_audio_paring.c
    pure-data/src/s_audio_dummy.c
    mocks/s_audio_dummy.cpp
    pure-data/src/s_file.c
    pure-data/src/s_inter.c
    pure-data/src/s_loader.c
    pure-data/src/s_main.c
    pure-data/src/s_midi.c
    pure-data/src/s_path.c
    pure-data/src/s_print.c
    pure-data/src/s_stuff.h
    pure-data/src/s_utf8.c
    pure-data/src/s_utf8.h
    pure-data/src/x_acoustics.c
    pure-data/src/x_arithmetic.c
    pure-data/src/x_array.c
    pure-data/src/x_connective.c
    pure-data/src/x_gui.c
    pure-data/src/x_interface.c
    pure-data/src/x_list.c
    pure-data/src/x_midi.c
    pure-data/src/x_misc.c
    pure-data/src/x_net.c
    pure-data/src/x_scalar.c
    pure-data/src/x_text.c
    pure-data/src/x_time.c
    pure-data/src/x_vexp.c
    pure-data/src/x_vexp.h
    pure-data/src/x_vexp_fun.c
    pure-data/src/x_vexp_if.c
)

set(PD_EXTRA_SOURCES
    pure-data/extra/bob~/bob~.c
    pure-data/extra/bonk~/bonk~.c
    pure-data/extra/choice/choice.c
    pure-data/extra/fiddle~/fiddle~.c
    pure-data/extra/loop~/loop~.c
    pure-data/extra/lrshift~/lrshift~.c
    pure-data/extra/pique/pique.c
    pure-data/extra/sigmund~/sigmund~.c
    pure-data/extra/stdout/stdout.c
)

source_group(pd FILES ${PD_SOURCES})
source_group(pdextra FILES ${PD_EXTRA_SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/pd/pure-data/src)
include_directories(${PROJECT_SOURCE_DIR}/distrib/rtaudio/rtaudio)

set(CMAKE_THREAD_PREFER_PTHREAD ON)

if(WIN32)
    include_directories(${PROJECT_SOURCE_DIR}/distrib/thread/pthreadwin)
    list(APPEND PD_EXTRA_SOURCES ${PROJECT_SOURCE_DIR}/distrib/thread/src/thd.c)
endif()

find_package(Threads REQUIRED)
add_definitions(-DPD=1 -DPD_INTERNAL=1 -DTHREAD_LOCKING=0 -DUSEAPI_MMIO=1)

include(TestBigEndian)
test_big_endian(IS_BIG_ENDIAN)
if(NOT ${IS_BIG_ENDIAN})
    add_definitions(-DLITTLE_ENDIAN=0x0001 -DBYTE_ORDER=LITTLE_ENDIAN)
endif()

set(PD_LINK_LIBRARIES)

if(UNIX AND NOT APPLE)
    add_definitions(-D_GNU_SOURCE)
    list(APPEND PD_LINK_LIBRARIES m)
    list(APPEND PD_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    set(LINUX True)
endif()

macro(add_osx_framework fwname target)
    find_library(FRAMEWORK_${fwname}
        NAMES ${fwname}
        PATHS ${CMAKE_OSX_SYSROOT}/System/Library
        PATH_SUFFIXES Frameworks
        NO_DEFAULT_PATH)
    if(${FRAMEWORK_${fwname}} STREQUAL FRAMEWORK_${fwname}-NOTFOUND)
        MESSAGE(ERROR ": Framework ${fwname} not found")
    else()
        target_link_libraries(${target} PUBLIC "${FRAMEWORK_${fwname}}/${fwname}")
        message(STATUS "Framework ${fwname} found at ${FRAMEWORK_${fwname}}")
    endif()
endmacro()

if(APPLE)
    include_directories(${CMAKE_OSX_SYSROOT}/System/Library)
    find_library(COREAUDIO_LIB CoreAudio)
    find_library(COREFOUNDATION_LIB CoreFoundation)
    find_library(AUDIOTOOLBOX_LIB AudioToolbox)
    list(APPEND PD_LINK_LIBRARIES rtaudio_static ${COREAUDIO_LIB} ${COREFOUNDATION_LIB} ${AUDIOTOOLBOX_LIB})  
endif()

if(WIN32)
    if(${CMAKE_SYSTEM_NAME} STREQUAL "WindowsStore")
        message("Building for UWP")
        set(FIPS_UWP 1)
    else()
        set(FIPS_UWP 0)
    endif()

    if (FIPS_UWP)
        set(CMAKE_CXX_STANDARD_LIBRARIES "WindowsApp.lib")
        set(CMAKE_C_STANDARD_LIBRARIES "WindowsApp.lib")
    else()
        set(CMAKE_CXX_STANDARD_LIBRARIES "-lkernel32 -lgdi32 -lole32 -lwinmm -luuid -lwsock32 -lws2_32")
        set(CMAKE_C_STANDARD_LIBRARIES ${CMAKE_CXX_STANDARD_LIBRARIES})
    endif()

    add_definitions(-DWINVER=0x0502 -D_WIN32_WINNT=0x0502)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mms-bitfields -O2 -funroll-loops -fomit-frame-pointer")
    set(CMAKE_CXX_FLAGS "-mms-bitfields -O2 -funroll-loops -fomit-frame-pointer")
    list(APPEND PLATFORM_LINK_LIBRARIES ${CMAKE_THREAD_LIBS_INIT})
    set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--export-all-symbols -lpthread")
    set(CMAKE_EXE_LINKER_FLAGS "-shared-libgcc -lpthread")
endif()

if(WITH_DUMMY_MIDI)
    list(APPEND PD_SOURCES pure-data/src/s_midi_dummy.c)
endif()

include(FindLibDL)
if(LIBDL_FOUND)
    list(APPEND PD_LINK_LIBRARIES ${LIBDL_LIBRARIES})
endif()

add_library(pd_core_shared SHARED ${PD_SOURCES} ${PD_EXTRA_SOURCES})
add_library(pd_core_static STATIC ${PD_SOURCES} ${PD_EXTRA_SOURCES})
target_link_libraries(pd_core_shared ${PD_LINK_LIBRARIES})
target_link_libraries(pd_core_static ${PD_LINK_LIBRARIES})

if(UNIX)
    set_target_properties(pd_core_static PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

add_subdirectory(cpd)
