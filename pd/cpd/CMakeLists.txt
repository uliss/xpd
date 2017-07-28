include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
set(CMP_SOURCES cpd.cpp cpd.h cpd_atom.cpp cpd_list.cpp cpd_env.cpp pr_log.cpp)

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
