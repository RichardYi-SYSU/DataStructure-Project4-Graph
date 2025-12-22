#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>

#include "../graph/GraphAL.h"

using namespace std;


const int INF=1e9;

/**
 * 最短路径算法（基于邻接表）
 * 适用于：有向 / 带权图
 */
class ShortestPath {
private:
    GraphAL* graph;                 // 图（邻接表）
    vector<long long> dist;          // 起点到各点的最短距离
    vector<int> prev;                // 最短路径的前驱结点


public:
    // 构造函数
    ShortestPath(GraphAL* g);

    // 计算最短路径（Dijkstra）
    void run(int startVertex);

    // 输出结果
    void printDistance() const;
    void printPath(int targetVertex) const;

    // Getter（用于可视化 / 生成路径）
    long long getDistance(int v) const;
    vector<int> getPath(int targetVertex) const;
};

#endif
