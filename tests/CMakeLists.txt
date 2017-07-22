include_directories(Catch/single_include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${CMAKE_BINARY_DIR}) # for config.h
add_definitions("-DTEST_DATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\"")

if(${WITH_COVERAGE})
    find_program(LCOV NAMES lcov PATHS /usr/bin /usr/local/bin)
    find_program (GCOV NAMES gcov-5 gcov-6 gcov PATHS /usr/bin /usr/local/bin)

    if(LCOV AND GCOV)
        message(STATUS "lcov found: ${LCOV}")
        message(STATUS "gcov found: ${GCOV}")
        add_custom_target(coverage
            COMMAND ${LCOV}
                --gcov-tool=${GCOV}
                --directory ${CMAKE_CURRENT_BINARY_DIR}
                --capture
                --output-file coverage.info
            COMMAND ${LCOV}
                --remove coverage.info 'Catch/*' '/usr/*' '/Applications/Xcode.app/*' 'src/m_pd.h'
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
    target_link_libraries("test_${name}" test_catch_main_lib pd_core_static xpd_static)
    set(_exec_cmd "test_${name}")

    add_test(NAME ${title} COMMAND ${_exec_cmd})
endmacro()

add_library(test_catch_main_lib STATIC tests_catch_main.cpp)
xpd_add_test(LocalServer localserver)
