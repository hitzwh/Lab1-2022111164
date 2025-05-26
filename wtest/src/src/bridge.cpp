#include "bridge.h"

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

//功能3 查询桥接词
string queryBridgeWords(const DirectedGraph& graph, string word1, string word2) {
    word1 = toLower(word1);
    word2 = toLower(word2);
    
    // 检查 word1 和 word2 是否存在
    if (graph.find(word1) == graph.end() && graph.find(word2) == graph.end()) {
        return "No \"" + word1 + "\" and \"" + word2 + "\" in the graph!";
    } else if (graph.find(word1) == graph.end()) {
        return "No \"" + word1 + "\" in the graph!";
    } else if (graph.find(word2) == graph.end()) {
        return "No \"" + word2 + "\" in the graph!";
    }

    vector<string> bridges;
    auto it = graph.find(word1);
    for (const auto& neighbor : it->second) {
        string bridge = neighbor.first;
        // 检查桥接词是否存在且指向 word2
        if(graph.find(bridge) != graph.end() && graph.find(bridge)->second.count(word2)){
            bridges.push_back(bridge);
        }
    }
    if (bridges.empty()) {
        return "No bridge words from \"" + word1 + "\" to \"" + word2 + "\"!";
    }

    string result = "The bridge words from \"" + word1 + "\" to \"" + word2 + "\" are: ";
    if (bridges.size() == 1) {
        result += "\"" + bridges[0] + "\"";
    } else {
        for (size_t i = 0; i < bridges.size(); ++i) {
            if (i == 0) {
                result += "\"" + bridges[i] + "\"";
            } else if (i == bridges.size() - 1) {
                result += " and \"" + bridges[i] + "\"";
            } else {
                result += ", \"" + bridges[i] + "\"";
            }
        }
    }
    return result + ".";
}