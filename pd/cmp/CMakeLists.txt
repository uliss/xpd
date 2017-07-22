set(CMP_SOURCES lib_cmp.cpp lib_cmp.h)

add_library(cmp STATIC ${CMP_SOURCES})
target_link_libraries(cmp pd_core_static)
