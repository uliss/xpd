set(SERVER_SRC 
    abstractserver.cpp
    abstractserverprocess.cpp
    arguments.cpp
    array.cpp
    audiodevice.cpp
    audiodevicemanager.cpp
    canvasobserver.cpp
    classinfo.cpp
    connection.cpp
    consoleobserver.cpp
    device.cpp
    libraryinfo.cpp
    localserver.cpp 
    logger.h
    logger.cpp
    mididevice.cpp
    mididevicemanager.cpp
    object.cpp
    objectlist.cpp
    objectproperties.cpp
    observer.cpp
    pd_arguments.cpp
    pd_canvas.cpp
    pd_localprocess.cpp
    pd_object.cpp
    propertyobserver.cpp
    servercanvas.cpp
    serverpath.cpp
    videodevice.cpp
    xlets.cpp
    pdLib.hpp pdServer.hpp 
#pdLib.cpp  pdServer.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/pd/pure-data/src)
include_directories(${CMAKE_SOURCE_DIR}/pd/cpd)
include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
include_directories(${PROJECT_SOURCE_DIR}/distrib/variant/include)

add_library(xpd_static STATIC ${SERVER_SRC})
add_library(xpd_shared SHARED ${SERVER_SRC})
target_link_libraries(xpd_static pd_core_static cpd)
target_link_libraries(xpd_shared pd_core_static cpd)
