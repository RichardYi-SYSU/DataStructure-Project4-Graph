#ifndef BFS_H
#define BFS_H

#include <vector>
#include <queue>
#include <iostream>

#include "../graph/GraphAML.h"

using namespace std;

/**
 * BFS 遍历（基于邻接多重表）
 * 用于无向图
 */
class BFS {
private:
    GraphAML* graph;                  // 图（邻接多重表）
    vector<bool> visited;             // 顶点访问标记
    vector<int> visitOrder;            // BFS 访问序列
    vector<pair<int,int>> treeEdges;   // BFS 生成树边集

public:
    // 构造函数
    BFS(GraphAML* g);

    // 执行 BFS
    void run(int startVertex);

    // 输出结果
    void printVisitOrder() const;
    void printTreeEdges() const;

    // 获取结果（供可视化 / 生成树使用）
    const vector<int>& getVisitOrder() const;
    const vector<pair<int,int>>& getTreeEdges() const;
};

#endif
