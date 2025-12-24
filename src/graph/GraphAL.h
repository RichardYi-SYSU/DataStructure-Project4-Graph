#ifndef GRAPH_AL_H
#define GRAPH_AL_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * 邻接表（Adjacency List）
 */
class GraphAL {
private:
    
    int vexNum;                     // 顶点数
    int edgeNum;                    // 边数

public:
    // 边结点
    struct EdgeNode {
        int to;            // 终点
        int weight;        // 权值
        EdgeNode* next;    // 下一条边

        EdgeNode(int t, int w, EdgeNode* n = nullptr)
            : to(t), weight(w), next(n) {}
    };

    // 顶点结点
    struct VertexNode {
        int data;          // 顶点编号
        EdgeNode* first;   // 指向第一条出边

        VertexNode(int d = 0) : data(d), first(nullptr) {}
    };

    vector<VertexNode> vertices;    // 顶点表
    
    // 构造函数
    GraphAL(int n = 0);

    // 析构函数
    ~GraphAL();

    // 基本信息
    int getVexNum() const;
    int getEdgeNum() const;

    // 建图
    void addEdge(int from, int to, int weight = 1);

    // 获取邻接信息
    EdgeNode* getFirstEdge(int v) const;

    // 输出
    void print() const;
};

#endif
