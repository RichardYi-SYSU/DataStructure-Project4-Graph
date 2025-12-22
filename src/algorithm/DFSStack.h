#ifndef DFSSTACK_H
#define DFSSTACK_H

#include <vector>
#include <iostream>

#include "../graph/GraphAML.h"     // 邻接多重表
#include "../container/Stack.h"    // 自定义栈

using namespace std;

/**
 * 非递归 DFS（基于栈）
 * 使用邻接多重表 GraphAML
 */
class DFSStack {
private:
    GraphAML* graph;               // 指向图（不负责创建）
    vector<bool> visited;          // 访问标记
    vector<int> visitOrder;        // 顶点访问序列
    vector<pair<int,int>> treeEdges; // DFS 生成树边集

public:
    // 构造函数：传入图
    DFSStack(GraphAML* g);

    // 执行非递归 DFS
    void run(int startVertex);

    // 输出结果
    void printVisitOrder() const;
    void printTreeEdges() const;

    // 获取结果（用于可视化 / 生成树）
    const vector<int>& getVisitOrder() const;
    const vector<pair<int,int>>& getTreeEdges() const;
};

#endif
