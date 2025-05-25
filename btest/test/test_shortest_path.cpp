#include <gtest/gtest.h>
#include "shortest_path/shortest_path.h"
#include <cstdlib>

// toLower函数测试
/*
TEST(ShortestPathTest, ToLowerCases) {
    GTEST_LOG_(INFO) << "Running ToLowerCases...";  // 使用 Google Test 的日志
    EXPECT_EQ(toLower("HELLO"), "hello");
    EXPECT_EQ(toLower("HeLLo"), "hello");
    EXPECT_EQ(toLower("123!@#"), "123!@#");
    EXPECT_EQ(toLower(""), "");
}
*/

// 1 3 6 8 12 节点都存在 + 多条路径 + 路径长度>=1 + 输入2个word + 有大写
TEST(ShortestPathTest, MultiPathShortest) {
    DirectedGraph graph;
    graph["aa"]["b"] = 1;
    graph["b"]["c"] = 2;
    graph["c"]["dd"] = 1;
    graph["aa"]["dd"] = 5;
    graph["b"]["dd"] = 3;
    graph["aa"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    graph["dd"];
    auto result = calcShortestPath(graph, "AA", "dD");
    EXPECT_EQ(result.first, "aa->b->dd");
    EXPECT_EQ(result.second, 4);
}

// 1 4 6 8 12  节点都存在 + 单条路径 + 路径长度>=1 + 输入2个word + 有大写
TEST(ShortestPathTest, SinglePath) {
    DirectedGraph graph;
    graph["x"]["y"] = 1;
    graph["y"]["zz"] = 1;
    graph["x"];  // 显式插入所有节点
    graph["y"];
    graph["zz"];
    auto result = calcShortestPath(graph, "X", "zz");
    EXPECT_EQ(result.first, "x->y->zz");
    EXPECT_EQ(result.second, 2);
}

// 1 5 8 12 节点都存在 + 没有路径 + 输入2个word + 有大写
TEST(ShortestPathTest, NoPath) {
    DirectedGraph graph;
    graph["x"]["y"] = 1;
    graph["z"]["w"] = 1;
    graph["x"];  // 显式插入所有节点
    graph["y"];
    graph["z"];
    graph["w"];
    auto result = calcShortestPath(graph, "X", "W");
    EXPECT_EQ(result.first, "No path found");
    EXPECT_EQ(result.second, -1);
}

// 2 5 8 11 有节点不存在 + 没有路径 + 输入2个word + 没有大写
TEST(ShortestPathTest, NodeNotExist) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    auto result = calcShortestPath(graph, "?", "123");
    EXPECT_EQ(result.first, "Nodes not found");
    EXPECT_EQ(result.second, -1);
}

// 2 5 9 12  有节点不在图中 + 没有路径 + 输入word个数<2 + 有大写
TEST(ShortestPathTest, TooFewWords_EmptyEnd) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    auto result = calcShortestPath(graph, "A", "");
    EXPECT_EQ(result.first, "Nodes not found");
    EXPECT_EQ(result.second, -1);
}

// 2 5 10 12 有节点不在图中 + 没有路径 + 输入word个数>2 + 有大写
TEST(ShortestPathTest, TooManyWords_MultipleStart) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    auto result = calcShortestPath(graph, "A B C", "B");
    EXPECT_EQ(result.first, "Nodes not found");
    EXPECT_EQ(result.second, -1);
}

//1 4 7 8 11 两个节点都存在 + 有1条路径 +  路径长度为0（自己到自己） + 输入word个数为2 + 没有大写
TEST(ShortestPathTest, SameNode) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    auto result = calcShortestPath(graph, "a", "a");
    EXPECT_EQ(result.first, "a");
    EXPECT_EQ(result.second, 0);
}


int main(int argc, char **argv) {
    GTEST_LOG_(INFO) << "Starting tests...";  // 使用 Google Test 的日志
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 