#ifndef DFS_H
#define DFS_H

#include <vector>
#include <iostream>

#include "../graph/GraphAML.h"

using namespace std;

/**
 * 递归 DFS（基于邻接多重表）
 * 用于无向图
 */
class DFS {
private:
    GraphAML* graph;                   // 图（邻接多重表）
    vector<bool> visited;              // 顶点访问标记
    vector<int> visitOrder;             // DFS 访问序列
    vector<pair<int,int>> treeEdges;    // DFS 生成树边集

    // 递归 DFS 核心函数
    void dfs(int v);

public:
    // 构造函数
    DFS(GraphAML* g);

    // 执行 DFS
    void run(int startVertex);

    // 输出结果
    void printVisitOrder() const;
    void printTreeEdges() const;

    // 获取结果（供对比 / 可视化 / 生成树使用）
    const vector<int>& getVisitOrder() const;
    const vector<pair<int,int>>& getTreeEdges() const;
};

#endif
