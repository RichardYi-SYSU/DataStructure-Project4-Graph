#ifndef GRAPH_AML_H
#define GRAPH_AML_H

#include <vector>
#include <iostream>
using namespace std;

/**
 * 邻接多重表（Adjacency Multilist）
 * 适用于 无向图
 */
class GraphAML {
private:
    

    int vexNum;                     // 顶点数
    int edgeNum;                    // 边数
    

public:

    // 边结点
    struct EdgeNode {
        int ivex;          // 边的一端顶点
        int jvex;          // 边的另一端顶点
        EdgeNode* ilink;   // 指向下一条依附于 ivex 的边
        EdgeNode* jlink;   // 指向下一条依附于 jvex 的边
        bool visited;      // DFS / BFS 中是否已访问该边

        EdgeNode(int i, int j)
            : ivex(i), jvex(j), ilink(nullptr), jlink(nullptr), visited(false) {}
    };
    // 顶点结点
    struct VertexNode {
        int data;          // 顶点编号
        EdgeNode* first;   // 指向第一条依附的边
        VertexNode(int d = 0) : data(d), first(nullptr) {}
    };

    vector<VertexNode> vertices;    // 顶点表

    // 构造函数
    GraphAML(int n = 0);

    // 析构函数
    ~GraphAML();

    // 基本信息
    int getVexNum() const;
    int getEdgeNum() const;

    // 建图
    void addEdge(int u, int v);

    // 遍历辅助
    EdgeNode* getFirstEdge(int v) const;
    int getOtherVertex(const EdgeNode* e, int v) const;

    // 重置边访问标记（多次 DFS / BFS 前用）
    void resetEdgeVisited();

    // 输出图结构（调试用）
    void print() const;
};

#endif
