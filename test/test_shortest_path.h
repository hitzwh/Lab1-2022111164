#ifndef TEST_SHORTEST_PATH_H
#define TEST_SHORTEST_PATH_H

#include <gtest/gtest.h>
#include "shortest_path/shortest_path.h"

// 测试类
class ShortestPathTest : public ::testing::Test {
protected:
    DirectedGraph graph;

    void SetUp() override {
        // 构建测试用的有向图
        // 多条路径的情况 (等价类3)
        // a -> b -> d
        // a -> c -> d
        graph["a"]["b"] = 1;
        graph["a"]["c"] = 1;
        graph["b"]["d"] = 1;
        graph["c"]["d"] = 1;
        graph["d"]["e"] = 2;

        // 单条路径的情况 (等价类4)
        // e -> f -> g
        graph["e"]["f"] = 1;
        graph["f"]["g"] = 1;
        graph["g"]["i"] = 1;
        graph["g"]["h"] = 1;


        // 无路径的情况 (等价类5)
        // h 和 i 之间没有路径
        graph["h"]["j"] = 1;
        graph["i"]["k"] = 1;

        // 确保所有节点都在graph中
        graph["b"];
        graph["c"];
        graph["d"];
        graph["f"];
        graph["g"];
        graph["j"];
        graph["k"];
    }
};

#endif // TEST_SHORTEST_PATH_H 