include_directories(Catch/single_include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/pd)
include_directories(${PROJECT_SOURCE_DIR}/distrib/variant/include)
include_directories(${CMAKE_BINARY_DIR}) # for config.h
add_definitions("-DTEST_DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")

if(WITH_COVERAGE)
#    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
    
    find_program(LCOV NAMES lcov PATHS /usr/bin /usr/local/bin)
    find_program (GCOV NAMES gcov gcov-7 gcov-6 gcov-5 PATHS /usr/bin /usr/local/bin)

    if(LCOV AND GCOV)
        message(STATUS "lcov found: ${LCOV}")
        message(STATUS "gcov found: ${GCOV}")
        add_custom_target(coverage
            COMMAND ${LCOV}
                --gcov-tool=${GCOV}
                --directory "${CMAKE_CURRENT_BINARY_DIR}/.."
                --capture
                --output-file coverage.info
            COMMAND ${LCOV}
                --extract coverage.info
                    "${CMAKE_SOURCE_DIR}/pd/cpd/*"
                    "${CMAKE_SOURCE_DIR}/src/*" 
                --output-file coverage.info
            COMMAND ${LCOV}
                --list coverage.info)

        add_custom_target(coverage_report
            COMMAND genhtml --output-directory ${CMAKE_BINARY_DIR}/coverage coverage.info
            COMMAND open ${CMAKE_BINARY_DIR}/coverage/index.html)
    endif()
endif()

macro(xpd_add_test title name)
    add_executable("test_${name}" "test_${name}.cpp")
    target_link_libraries("test_${name}" test_catch_main_lib xpd_static pd_core_static)
    set(_exec_cmd "test_${name}")

    add_test(NAME ${title} COMMAND ${_exec_cmd})
endmacro()

add_library(test_catch_main_lib STATIC tests_catch_main.cpp)

xpd_add_test(atom cpd_atom)
xpd_add_test(list cpd_list)
xpd_add_test(env cpd_env)
xpd_add_test(canvas cpd_canvas)
xpd_add_test(cpd cpd)
xpd_add_test(object cpd_object)
xpd_add_test(catcher cpd_catcher)

xpd_add_test(PdObject pdobject)
xpd_add_test(LocalServer localserver)
xpd_add_test(ObjectList objectlist)
