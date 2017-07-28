include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
set(CMP_SOURCES
    cpd.h  cpd.cpp 
    cpd_atom.h cpd_atom.cpp 
    cpd_canvas.h cpd_canvas.cpp
    cpd_catcher.h cpd_catcher.cpp
    cpd_list.h cpd_list.cpp 
    cpd_env.h cpd_env.cpp 
    cpd_object.h cpd_object.cpp
    cpd_types.h cpd_types.cpp 
    pr_log.cpp)

if(WIN32)
    add_definitions(-DCPD_INTERNAL)
endif()

if(WITH_COVERAGE)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

add_library(cpd STATIC ${CMP_SOURCES})

if(UNIX)
    set_target_properties(cpd PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

target_link_libraries(cpd pd_core_static)
