#ifndef BRIDGE_H
#define BRIDGE_H

#include <bits/stdc++.h>
using namespace std;

// 定义有向图类型：邻接表，节点到相邻节点及其权重的映射
using DirectedGraph = map<string, map<string, int>>;

// 辅助函数：将字符串转换为小写
string toLower(const string& str);

// 声明被测试的函数
string queryBridgeWords(const DirectedGraph& graph, string word1, string word2);

#endif // SHORTEST_PATH_H 