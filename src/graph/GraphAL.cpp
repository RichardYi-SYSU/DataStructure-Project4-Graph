#include "GraphAL.h"

/* ================= 构造与析构 ================= */

GraphAL::GraphAL(int n)
{
    vexNum = n;
    edgeNum = 0;
    vertices.resize(vexNum);

    // 初始化顶点表（编号从 1 开始）
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = VertexNode(i + 1);
    }
}

GraphAL::~GraphAL()
{
    // 释放每个顶点的出边链表
    for (int i = 0; i < vexNum; ++i) {
        EdgeNode* e = vertices[i].first;
        while (e) {
            EdgeNode* next = e->next;
            delete e;
            e = next;
        }
        vertices[i].first = nullptr;
    }
}

/* ================= 基本信息 ================= */

int GraphAL::getVexNum() const
{
    return vexNum;
}

int GraphAL::getEdgeNum() const
{
    return edgeNum;
}

/* ================= 建图 ================= */

void GraphAL::addEdge(int from, int to, int weight)
{
    // 顶点编号合法性检查
    if (from < 1 || from > vexNum || to < 1 || to > vexNum) {
        cout << "Invalid edge: "
             << from << " -> " << to << endl;
        return;
    }

    // 头插法插入出边
    EdgeNode* e = new EdgeNode(to, weight, vertices[from - 1].first);
    vertices[from - 1].first = e;
    edgeNum++;
}

/* ================= 邻接信息 ================= */

GraphAL::EdgeNode* GraphAL::getFirstEdge(int v) const
{
    if (v < 1 || v > vexNum) return nullptr;
    return vertices[v - 1].first;
}

/* ================= 输出 ================= */

void GraphAL::print() const
{
    cout << "Graph (Adjacency List):" << endl;
    for (int i = 0; i < vexNum; ++i) {
        cout << "Vertex " << vertices[i].data << ": ";
        EdgeNode* e = vertices[i].first;
        while (e) {
            cout << "->(" << e->to
                 << ", w=" << e->weight << ") ";
            e = e->next;
        }
        cout << endl;
    }
}
