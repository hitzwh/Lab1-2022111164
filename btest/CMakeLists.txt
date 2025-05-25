cmake_minimum_required(VERSION 4.0.2)  # cmake -G "MinGW Makefiles" ..
project(GTESTWIN)

# 启用代码覆盖率
option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# 头文件目录
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src/include")
# 源文件目录
AUX_SOURCE_DIRECTORY("${CMAKE_CURRENT_SOURCE_DIR}/src/src" DIR_SRCS)

# 生成可执行文件
add_executable(gtest_win ./src/main.cpp ${DIR_SRCS})

# 增加测试工程
add_subdirectory(test)

if(ENABLE_COVERAGE)
    add_custom_target(coverage
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_SOURCE_DIR}/coverage.cmake
        DEPENDS gtest_win gtest_win_test
        COMMENT "Generating coverage report")
endif()
