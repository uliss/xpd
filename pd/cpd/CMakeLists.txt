include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
set(CMP_SOURCES lib_cpd.cpp lib_cpd.h atom.cpp atomlist.cpp pr_log.cpp)

add_library(cpd STATIC ${CMP_SOURCES})

if(UNIX)
    set_target_properties(cpd PROPERTIES COMPILE_FLAGS "-fPIC")
endif()

target_link_libraries(cpd)
