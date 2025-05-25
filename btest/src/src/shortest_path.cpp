#include "shortest_path/shortest_path.h"

// 辅助函数：将字符串转换为小写
string toLower(const string& str) {
    string lowerStr = str;
    for(int i = 0; i < lowerStr.size(); i++){
        if(lowerStr[i] >= 'A' && lowerStr[i] <= 'Z'){
            lowerStr[i] = lowerStr[i] + 32;
        }
    }
    return lowerStr;
}

// 计算最短路径的函数实现
pair<string, int> calcShortestPath(const DirectedGraph& graph, string word1, string word2) {
    word1 = toLower(word1);
    word2 = toLower(word2);

    // Check if nodes exist
    if (graph.find(word1) == graph.end() || graph.find(word2) == graph.end()) {
        return {"Nodes not found", -1};
    }

    // Special case: same node
    if (word1 == word2) {
        return {word1, 0};
    }

    map<string, int> dist;
    map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    // Initialize distances
    for (const auto& node : graph) {
        dist[node.first] = INT_MAX;
    }
    dist[word1] = 0;
    pq.push({0, word1});

    while (!pq.empty()) {
        int currentDist = pq.top().first;
        string currentNode = pq.top().second;
        pq.pop();

        if (currentDist > dist[currentNode]) continue;

        if (currentNode == word2) break;  // Found target node

        auto it = graph.find(currentNode);
        if (it != graph.end()) {
            const auto& neighbors = it->second;
            for (const auto& neighbor : neighbors) {
                int weight = neighbor.second;
                if (dist[neighbor.first] > dist[currentNode] + weight) {
                    dist[neighbor.first] = dist[currentNode] + weight;
                    prev[neighbor.first] = currentNode;
                    pq.push({dist[neighbor.first], neighbor.first});
                }
            }
        }
    }

    // Check if path exists
    if (dist[word2] == INT_MAX) {
        return {"No path found", -1};
    }

    // Build path
    vector<string> path;
    string node = word2;
    while (node != word1) {
        path.push_back(node);
        node = prev[node];
    }
    path.push_back(word1);
    reverse(path.begin(), path.end());

    string pathStr;
    for (size_t i = 0; i < path.size(); ++i) {
        pathStr += path[i];
        if (i != path.size() - 1) pathStr += "->";
    }
    return {pathStr, dist[word2]};
} 