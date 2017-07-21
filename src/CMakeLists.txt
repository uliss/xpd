set(SERVER_SRC 
    abstractserver.cpp
    abstractserverprocess.cpp
pdLib.hpp pdServer.hpp 
#pdLib.cpp  pdServer.cpp
    )

include_directories(${CMAKE_SOURCE_DIR}/pd/pure-data/src)

add_library(xpd_static STATIC ${SERVER_SRC})
add_library(xpd_shared SHARED ${SERVER_SRC})
target_link_libraries(xpd_static pd_core_static)
target_link_libraries(xpd_shared pd_core_static)
