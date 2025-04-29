#include <bits/stdc++.h>
#include <windows.h>
const double small = 1e-8;
using namespace std;
// 定义有向图类型：邻接表，节点到相邻节点及其权重的映射
using DirectedGraph = map<string, map<string, int>>;
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

// 辅助函数：清洗文本，替换非字母为空格
string cleanText(const string& text) {
    string cleaned = text;
    for(int i=0;i<cleaned.size();i++){
        if(!isalpha(cleaned[i])){
            cleaned[i] =' ';
        }
    }
    return cleaned;
}

// 辅助函数：分割字符串为单词列表
vector<string> splitWords(const string& text) {
    string cleaned = cleanText(text);
    //流式分割，忽略单词之间连续的空格
    istringstream iss(cleaned);
    vector<string> words;
    string word;
    while (iss >> word) {
        words.push_back(toLower(word));
    }
    return words;
}

//展示最短路径
void showShortestPath(vector<string> path,const DirectedGraph& graph) {
    // 打开dot文件
    std::ofstream dotFile("path.dot");
    if (!dotFile.is_open()) {
        std::cerr << "无法打开 path.dot 文件" << std::endl;
        return;
    }
    map<string,map<string,bool>> Link;
    for(int i=0;i<path.size()-1;i++){
        Link[path[i]][path[i+1]]=true;
    }
    // 写入dot文件的起始部分
    dotFile << "digraph G {" << std::endl;

    for (const auto& node : graph) {
        const std::string& from = node.first;
        const auto& neighbors = node.second;
        // 遍历当前节点的所有邻居节点
        for (const auto& edge : neighbors) {
            const std::string& to = edge.first;
            int weight = edge.second;
            if(Link[from].find(to)==Link[from].end()){
                // 写入边的信息，包含权重
                dotFile << "    \"" << from << "\" -> \"" << to << "\" [label=\"" << weight << "\"];" << std::endl;
            }
            else{
                dotFile << "    \"" << from << "\" -> \"" << to << "\" [label=\"" << weight 
                << "\", color=\"red\", penwidth=2.0];" << std::endl;
                dotFile << "    \"" << from << "\" [style=filled, fillcolor=red];" << std::endl; 
                dotFile << "    \"" << to << "\" [style=filled, fillcolor=red];" << std::endl; 
            }
        }
    }

    // 写入dot文件的结束部分
    dotFile << "}" << std::endl;
    dotFile.close();

    // 准备命令行参数
    std::string command = "dot -Tpng path.dot -o path.png";
    std::wstring wCommand(command.begin(), command.end());

    // 初始化进程信息结构体
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // 创建新进程
    if (!CreateProcessW(nullptr, const_cast<LPWSTR>(wCommand.c_str()), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        std::cerr << "执行dot命令时出错" << std::endl;
        return;
    }

    // 等待进程结束
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取进程退出码
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // 关闭进程和线程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode == 0) {
        std::cout << "有向图已成功生成到 path.png" << std::endl;
          // 使用 ShellExecuteW 打开图片文件
          HINSTANCE result = ShellExecuteW(
            nullptr,                   // 无父窗口
            L"open",                   // 操作类型：打开文件
            L"path.png",               // 文件路径
            nullptr,                   // 无参数
            nullptr,                   // 使用当前工作目录
            SW_SHOWNORMAL              // 显示方式：正常窗口
        );

        // 检查是否执行成功
        if ((INT_PTR)result <= 32) {
            std::cerr << "无法打开 path.png，错误代码: " << (INT_PTR)result << std::endl;
        }
    }
    else {
        std::cerr << "执行dot命令时出错" << std::endl;
    }
}

// 功能1：读取文件生成有向图
DirectedGraph buildGraph(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        exit(0);
    }

    stringstream buffer;
    //将文件中的全部内容读到buffer中
    buffer << file.rdbuf();
    file.close();

    vector<string> words = splitWords(buffer.str());
    DirectedGraph graph;
    int j = words.size();
    for (int i = 0; i < words.size() - 1; ++i) {
        string from = words[i];
        string to = words[i + 1];
        graph[from][to]++; // 更新边权重
        graph[to];
    }
    return graph;
}

// 功能2：展示有向图，利用dot生成展示有向图
void showDirectedGraph(const std::map<std::string, std::map<std::string, int>>& graph) {
    // 打开dot文件
    std::ofstream dotFile("graph.dot");
    if (!dotFile.is_open()) {
        std::cerr << "无法打开 graph.dot 文件" << std::endl;
        return;
    }

    // 写入dot文件的起始部分
    dotFile << "digraph G {" << std::endl;

    // 遍历图中的每个节点
    for (const auto& node : graph) {
        const std::string& from = node.first;
        const auto& neighbors = node.second;
        // 遍历当前节点的所有邻居节点
        for (const auto& edge : neighbors) {
            const std::string& to = edge.first;
            int weight = edge.second;
            // 写入边的信息，包含权重
            dotFile << "    \"" << from << "\" -> \"" << to << "\" [label=\"" << weight << "\"];" << std::endl;
        }
    }

    // 写入dot文件的结束部分
    dotFile << "}" << std::endl;
    dotFile.close();

    // 准备命令行参数
    std::string command = "dot -Tpng graph.dot -o graph.png";
    std::wstring wCommand(command.begin(), command.end());

    // 初始化进程信息结构体
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // 创建新进程
    if (!CreateProcessW(nullptr, const_cast<LPWSTR>(wCommand.c_str()), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        std::cerr << "执行dot命令时出错" << std::endl;
        return;
    }

    // 等待进程结束
    WaitForSingleObject(pi.hProcess, INFINITE);

    // 获取进程退出码
    DWORD exitCode;
    GetExitCodeProcess(pi.hProcess, &exitCode);

    // 关闭进程和线程句柄
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    if (exitCode == 0) {
        std::cout << "有向图已成功生成到 graph.png" << std::endl;
    } else {
        std::cerr << "执行dot命令时出错" << std::endl;
    }
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

// 功能4：生成新文本
// 用户输入的文本将按一开始定义的规则处理
string generateNewText(const DirectedGraph& graph, const string& inputText) {
    vector<string> words = splitWords(inputText);
    vector<string> newWords;
    
    for (size_t i = 0; i < words.size(); ++i) {
        newWords.push_back(words[i]);
        if (i < words.size() - 1) {
            string word1 = words[i];
            string word2 = words[i + 1];
            vector<string> bridges;

            //  检查 word1 和 word2 是否均存在
            if (graph.find(word1) == graph.end() || graph.find(word2) == graph.end()) {
                continue;
            }
            else{
                auto it = graph.find(word1);
                for (const auto& neighbor : it->second) {
                    for(const auto & neighbor2 : graph.find(neighbor.first)->second){
                        if (neighbor2.first == word2) {
                            bridges.push_back(neighbor.first);
                        }
                    }
                }  
            }
            //  随机插入桥接词
            if (!bridges.empty()) {
                random_device rd;
                mt19937 gen(rd());
                uniform_int_distribution<> dis(0, bridges.size() - 1);
                newWords.push_back(bridges[dis(gen)]);
            }
        }
    }
    
    stringstream result;
    for (const string& word : newWords) {
        result << word << " ";
    }
    // 手动去除末尾的空格
    string output = result.str();
    size_t end = output.find_last_not_of(" \t\n\r");
    if (end != string::npos) {
        output = output.substr(0, end + 1);
    } else {
        output.clear();
    }
    return output;
}

// 功能5：计算最短路径（Dijkstra算法）
pair<string, int> calcShortestPath(DirectedGraph graph, string word1, string word2) {
    word1 = toLower(word1);
    word2 = toLower(word2);

    if (graph.find(word1) == graph.end() || graph.find(word2) == graph.end()) {
        return {"Nodes not found", -1};
    }

    map<string, int> dist;
    map<string, string> prev;
    priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;

    //初始化距离为最大值
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

        for (const auto& neighbor : graph.at(currentNode)) {
            int weight = neighbor.second;
            if (dist[neighbor.first] > dist[currentNode] + weight) {
                dist[neighbor.first] = dist[currentNode] + weight;
                prev[neighbor.first] = currentNode;
                pq.push({dist[neighbor.first], neighbor.first});
            }
        }
    }

    if (dist[word2] == INT_MAX) {
        return {"No path found", -1};
    }

    //打印路径
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
    if(graph.size()>1000){
        return {pathStr, dist[word2]};
    }
    showShortestPath(path,graph);
    return {pathStr, dist[word2]};
}

// 功能6：计算PageRank
double calPageRank(const DirectedGraph& graph, const string& word) {
    const double d = 0.85;
    int N = graph.size();
    map<string, double> pr, newPr;

    // 初始化PR值
    for (const auto& node : graph) {
        pr[node.first] = 1.0 / N;
    }

    vector<string> danglingNodes;
    for (const auto& node : graph) {
        if (node.second.empty()) {     
            danglingNodes.push_back(node.first);    
        }
    }
    // 迭代直到收敛
    for (int iter = 0; iter < 100; ++iter) {
        double maxDiff = 0.0;
        newPr.clear();
        //对悬空节点的处理
        //悬空节点的PR值由其余节点均摊
        double danglingSum = 0.0;
        for(const auto& dang : danglingNodes){
            danglingSum += pr[dang];
        }
        double danglingContribution = (d * danglingSum) / N;
        //遍历图中节点
        for (const auto& node : graph) {
            string u = node.first;
            double sum = 0.0;
            //遍历寻找指向node的节点
            for (const auto& inNode : graph) {
                if (inNode.second.find(u) != inNode.second.end()) {
                    int outDegree = inNode.second.size();
                    sum += pr[inNode.first] / outDegree;
                }           
            }
            newPr[u] = (1 - d) / N + d * sum + danglingContribution;
            if(abs(pr[u]-newPr[u])>maxDiff){
                maxDiff = abs(pr[u]-newPr[u]);
            }
        }
        if(abs(pr[word]-newPr[word])<small&&iter>=10){
            return pr.find(word) != pr.end() ? pr[word] : 0.0;
        }
        pr = newPr;
        double total = 0.0;
        for(const auto& prVal : pr){
            total += prVal.second;
        }
        cout<<iter+1<<": total pr "<<total<<endl;
    }

    return pr.find(word) != pr.end() ? pr[word] : 0.0;
}

// 功能7：随机游走
string randomWalk(const DirectedGraph& graph) {
    if (graph.empty()) return "Graph is empty!";

    vector<string> nodes;
    for (const auto& node : graph) {
        nodes.push_back(node.first);
    }

    //随机选点
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, nodes.size() - 1);
    string currentNode = nodes[dis(gen)];
    string path = currentNode;

    map<string, map<string, int>> visitedEdges;

    while (true) {
        const auto& neighbors = graph.find(currentNode)->second;
        if (neighbors.empty()) break;

        vector<string> vertex;
        for (const auto& neighbor : neighbors) {
            vertex.insert(vertex.end(), neighbor.second, neighbor.first); // 按权重复制节点
        }

        if (vertex.empty()) break;

        uniform_int_distribution<> edgeDis(0, vertex.size() - 1);
        string nextNode = vertex[edgeDis(gen)];

        // 检查边是否已访问
        auto& currentEdges = visitedEdges[currentNode];
        auto edgeIt = currentEdges.find(nextNode);
        if (edgeIt != currentEdges.end() && edgeIt->second >= 1) {
            break; // 已访问过这条边，终止
        }
        visitedEdges[currentNode][nextNode]++;

        path += " " + nextNode;
        currentNode = nextNode;
    }

    //将结果写入文件
    ofstream outFile("random.txt");
    if (outFile.is_open()) {
        outFile << path; // 写入路径
        outFile.close();
    } else {
        cerr << "Error: Unable to write to random.txt" << endl;
    }

    return path;
}

// 主函数
int main(int argc, char** argv) {
    string filename;
    DirectedGraph graph;
    // 处理文件输入
    if (argc >= 2) {
        filename = argv[1];
        graph = buildGraph(filename);
    } else {
        cout << "Enter file path: ";
        getline(cin,filename);
        graph = buildGraph(filename);
    }

    int choice;
    while (true) {
        cout.flush();
        cout << "\n=== Menu ===" << endl;
        cout << "1. Show Directed Grasph" << endl;
        cout << "2. Query Bridge Words" << endl;
        cout << "3. Generate New Text" << endl;
        cout << "4. Calculate Shortest Path" << endl;
        cout << "5. Calculate PageRank" << endl;
        cout << "6. Random Walk" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        if(!(cin>>choice)){
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.clear();
            choice=0;
            cout<<"Invalid choice. Please try again."<<endl;
            continue;
        }
        getchar();
        switch (choice) {
            case 1:
                showDirectedGraph(graph);
                break;
            case 2: {
                string line;
                cout << "Enter two words to query bridge words: ";
                getline(cin, line);
                vector<string> words = splitWords(line);
                if (words.size() != 2) {
                    cout << "Error: Please enter exactly two words." << endl;
                } else {
                    cout << queryBridgeWords(graph, words[0], words[1]) << endl;
                }
                break;
            }
            case 3: {
                string inputText;
                cout << "Enter new text: ";
                getline(cin, inputText);
                cout << "Generated text: " << generateNewText(graph, inputText) << endl;
                break;
            }
            case 4: {
                string inputPath;
                cout <<"input one or two word:";
                getline(cin,inputPath);
                vector<string> pathWords = splitWords(inputPath);
                if(pathWords.size() == 1){
                    for(auto it = graph.begin();it!=graph.end();it++){
                        cout<<"for word "<<pathWords[0]<<"->"<<" word "<<it->first<<":"<<endl;
                        auto [path, length] = calcShortestPath(graph, pathWords[0], it->first);
                        cout << "Shortest Path: " << path << endl;
                        cout << "Path Length: " << length << endl;
                        cout<<"\n";
                    }
                }
                else if(pathWords.size() == 2){
                    string word1 = pathWords[0];
                    string word2 = pathWords[1];
                    auto [path, length] = calcShortestPath(graph, word1, word2);
                    cout<<"for word "<<pathWords[0]<<"->"<<" word "<<pathWords[1]<<":"<<endl;
                    cout << "Shortest Path: " << path << endl;
                    cout << "Path Length: " << length << endl;
                }
                else{
                    cout<<"Too many inputs!";
                }
                break;
            }
            case 5: {
                string word;
                cout << "Enter word for PageRank: ";
                getline(cin, word);
                double pr = calPageRank(graph, word);
                cout << "PageRank of \"" << word << "\": " << pr << endl;
                break;
            }
            case 6:
                cout << "Random Walk Path: " << randomWalk(graph) << endl;
                break;
            case 0:
                cout << "Exiting program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}