#include "GraphAML.h"

/* ================= 构造与析构 ================= */

GraphAML::GraphAML(int n)
{
    vexNum = n;
    edgeNum = 0;
    vertices.resize(vexNum);

    // 初始化顶点表
    for (int i = 0; i < vexNum; ++i) {
        vertices[i] = VertexNode(i + 1);   // 顶点编号从 1 开始
    }
}

GraphAML::~GraphAML()
{
    // 邻接多重表中，每条边只需要释放一次
    for (int i = 0; i < vexNum; ++i) {
        EdgeNode* e = vertices[i].first;
        while (e) {
            EdgeNode* next;
            // 判断当前顶点是 ivex 还是 jvex
            if (e->ivex == i + 1)
                next = e->ilink;
            else
                next = e->jlink;

            // 只在 ivex 这一侧释放，避免重复 delete
            if (e->ivex == i + 1) {
                delete e;
            }
            e = next;
        }
    }
}

/* ================= 基本信息 ================= */

int GraphAML::getVexNum() const
{
    return vexNum;
}

int GraphAML::getEdgeNum() const
{
    return edgeNum;
}

/* ================= 建图 ================= */

void GraphAML::addEdge(int u, int v)
{
    // u, v 是顶点编号（从 1 开始）
    if (u < 1 || u > vexNum || v < 1 || v > vexNum) {
        cout << "Invalid edge: " << u << " " << v << endl;
        return;
    }

    EdgeNode* e = new EdgeNode(u, v);

    // 插入到 u 的边表
    e->ilink = vertices[u - 1].first;
    vertices[u - 1].first = e;

    // 插入到 v 的边表
    e->jlink = vertices[v - 1].first;
    vertices[v - 1].first = e;

    edgeNum++;
}

/* ================= 遍历辅助 ================= */

GraphAML::EdgeNode* GraphAML::getFirstEdge(int v) const
{
    if (v < 1 || v > vexNum) return nullptr;
    return vertices[v - 1].first;
}

int GraphAML::getOtherVertex(const EdgeNode* e, int v) const
{
    // 已知边 e 和顶点 v，返回另一端
    if (e->ivex == v)
        return e->jvex;
    else
        return e->ivex;
}

/* ================= 辅助功能 ================= */

void GraphAML::resetEdgeVisited()
{
    // 遍历所有边，重置 visited 标志
    for (int i = 0; i < vexNum; ++i) {
        EdgeNode* e = vertices[i].first;
        while (e) {
            e->visited = false;

            if (e->ivex == i + 1)
                e = e->ilink;
            else
                e = e->jlink;
        }
    }
}

void GraphAML::print() const
{
    cout << "Graph (Adjacency Multilist):" << endl;
    for (int i = 0; i < vexNum; ++i) {
        cout << "Vertex " << vertices[i].data << ": ";
        EdgeNode* e = vertices[i].first;
        while (e) {
            int other = getOtherVertex(e, vertices[i].data);
            cout << other << " ";
            if (e->ivex == vertices[i].data)
                e = e->ilink;
            else
                e = e->jlink;
        }
        cout << endl;
    }
}
