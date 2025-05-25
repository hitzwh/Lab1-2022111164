cmake_minimum_required(VERSION 4.0.2)
project(GTESTWIN_TEST)

#启用代码覆盖率
option(ENABLE_COVERAGE "Enable coverage reporting" ON)
if(ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif()

# gtest库相关
add_subdirectory(./googletest)  # 编译gtest
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)  # 包含gtest等头文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include)  # 包含gtest等头文件

# 头文件目录
include_directories("../src/include")
# 源文件目录
file(GLOB SRCS "../src/src/*.cpp")
# 测试代码目录
file(GLOB TEST_SRCS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

# 生成可执行程序
add_executable(gtest_win_test ${SRCS} ${TEST_SRCS})

# 链接测试库
target_link_libraries(gtest_win_test
        PRIVATE 
        gtest
        gtest_main
        gmock
        gmock_main
        pthread)
