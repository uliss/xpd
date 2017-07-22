include_directories(${PROJECT_SOURCE_DIR}/distrib/spdlog/include)
set(CMP_SOURCES lib_cpd.cpp lib_cpd.h)

add_library(cpd STATIC ${CMP_SOURCES})
target_link_libraries(cpd)
