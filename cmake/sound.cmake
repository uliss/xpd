option(WITH_DUMMY "Build dummy audio and midi modules" ON)
option(WITH_DUMMY_AUDIO "Build dummy audio module" ON)
option(WITH_DUMMY_MIDI "Build dummy midi module" ON)
if(WITH_DUMMY)
    set(WITH_DUMMY_AUDIO ON CACHE BOOL "" FORCE)
    set(WITH_DUMMY_MIDI ON CACHE BOOL "" FORCE)
endif()

# Dummy
if(WITH_DUMMY_AUDIO OR WITH_DUMMY_MIDI)
    add_definitions(-DUSEAPI_DUMMY)
endif()

if(NOT WITH_ALSA_AUDIO AND
        NOT WITH_JACK AND
        NOT WITH_OSS AND
        NOT WITH_PORTAUDIO AND
        NOT WITH_MMIO AND
        NOT WITH_DUMMY_AUDIO)
    message(FATAL_ERROR "At least one sound module required! See `cmake -L` for available config options.
        You can build with dummy audio with cmake -DWITH_DUMMY_AUDIO=ON option.")
endif()

if(NOT WITH_ALSA_MIDI AND
        NOT WITH_OSS AND
        NOT WITH_PORTMIDI AND
        NOT WITH_DUMMY_MIDI)
    message(FATAL_ERROR "At least one midi module required! See `cmake -L` for available config options.
        You can build with dummy midi with cmake -DWITH_DUMMY_MIDI=ON option.")
endif()
