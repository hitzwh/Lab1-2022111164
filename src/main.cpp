#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include "shortest_path/shortest_path.h"

using namespace std;

int main() {
    // 创建一个示例图
    DirectedGraph graph;
    
    // 添加一些边
    graph["a"]["b"] = 1;
    graph["b"]["c"] = 2;
    graph["c"]["d"] = 1;
    graph["a"]["d"] = 5;
    graph["b"]["d"] = 3;
    
    // 确保所有节点都在图中
    graph["a"];
    graph["b"];
    graph["c"];
    graph["d"];

/*
    // 测试一些最短路径
    cout << "Testing shortest paths:" << endl;
    
    // 测试从 a 到 d 的最短路径
    auto result1 = calcShortestPath(graph, "a", "D");
    cout << "Shortest path from a to d: " << result1.first << " (distance: " << result1.second << ")" << endl;
    
    // 测试从 a 到 c 的最短路径
    auto result2 = calcShortestPath(graph, "a", "c");
    cout << "Shortest path from a to c: " << result2.first << " (distance: " << result2.second << ")" << endl;
    
    // 测试不存在的节点
    auto result3 = calcShortestPath(graph, "a", "z");
    cout << "Path from a to z: " << result3.first << " (distance: " << result3.second << ")" << endl;


*/
    return 0;
}
