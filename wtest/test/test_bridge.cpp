#include <gtest/gtest.h>
#include "bridge.h"
#include <cstdlib>


// 测试用例0: 考虑空图的情况
TEST(ShortestPathTest, EmptyGraph) {
    DirectedGraph graph;
    string result = queryBridgeWords(graph, "?", "1");
    EXPECT_EQ(result, "No \"?\" and \"1\" in the graph!");
}

// 测试用例1：word1和word2都不在图中
TEST(ShortestPathTest, BothWordsNotInGraph) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["b"]["c"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    string result = queryBridgeWords(graph, "?", "1");
    EXPECT_EQ(result, "No \"?\" and \"1\" in the graph!");
}

// 测试用例2：只有word1不在图中
TEST(ShortestPathTest, OnlyWord1NotInGraph) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["b"]["c"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    string result = queryBridgeWords(graph, "R", "a");
    EXPECT_EQ(result, "No \"r\" in the graph!");
}

// 测试用例3：只有word2不在图中
TEST(ShortestPathTest, OnlyWord2NotInGraph) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["b"]["c"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    string result = queryBridgeWords(graph, "a", "X");
    EXPECT_EQ(result, "No \"x\" in the graph!");
}

// 测试用例4：word1和word2之间没有桥接词
TEST(ShortestPathTest, NoBridgeWord) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["c"]["d"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    graph["d"];
    string result = queryBridgeWords(graph, "A", "D");
    EXPECT_EQ(result, "No bridge words from \"a\" to \"d\"!");
}

// 测试用例5：word1和word2之间有一个桥接词
TEST(ShortestPathTest, OneBridgeWord) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["b"]["c"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    string result = queryBridgeWords(graph, "a", "c");
    EXPECT_EQ(result, "The bridge words from \"a\" to \"c\" are: \"b\".");
}

// 测试用例6：word1和word2之间有两个桥接词
TEST(ShortestPathTest, TwoBridgeWords) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["a"]["c"] = 1;
    graph["b"]["d"] = 1;
    graph["c"]["d"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    graph["d"];
    string result = queryBridgeWords(graph, "a", "d");
    EXPECT_EQ(result, "The bridge words from \"a\" to \"d\" are: \"b\" and \"c\".");
}

// 测试用例7：word1和word2之间有三个桥接词
TEST(ShortestPathTest, ThreeBridgeWords) {
    DirectedGraph graph;
    graph["a"]["b"] = 1;
    graph["a"]["c"] = 1;
    graph["a"]["d"] = 1;
    graph["b"]["e"] = 1;
    graph["c"]["e"] = 1;
    graph["d"]["e"] = 1;
    graph["a"];  // 显式插入所有节点
    graph["b"];
    graph["c"];
    graph["d"];
    graph["e"];
    string result = queryBridgeWords(graph, "a", "e");
    EXPECT_EQ(result, "The bridge words from \"a\" to \"e\" are: \"b\", \"c\" and \"d\".");
}

int main(int argc, char **argv) {
    GTEST_LOG_(INFO) << "Starting tests...";  // 使用 Google Test 的日志
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 