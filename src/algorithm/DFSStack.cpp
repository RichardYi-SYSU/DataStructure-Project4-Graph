#include "DFSStack.h"

/* ================= 构造函数 ================= */

DFSStack::DFSStack(GraphAML* g)
{
    graph = g;
}

/* ================= 非递归 DFS（标准实现） ================= */

void DFSStack::run(int startVertex)
{
    int n = graph->getVexNum();

    visited.assign(n + 1, false);
    visitOrder.clear();
    treeEdges.clear();
    graph->resetEdgeVisited();

    vector<int> parent(n + 1, -1);
    Stack S;

    // 压入起点帧
    S.push({startVertex, graph->getFirstEdge(startVertex)});
    parent[startVertex] = -1;

    while (!S.isEmpty())
    {
        Frame cur;
        S.pop(cur);   // ⭐ 每一轮只 pop 一次

        int v = cur.v;

        // 第一次进入 v（等价于 dfs(v)）
        if (!visited[v])
        {
            visited[v] = true;
            visitOrder.push_back(v);

            if (parent[v] != -1)
                treeEdges.emplace_back(parent[v], v);
        }

        bool foundChild = false;

        // 从 cur.edge 开始，找下一个可以进入的子结点
        while (cur.edge != nullptr)
        {
            GraphAML::EdgeNode* e = cur.edge;

            // 推进 edge（模拟 for 循环）
            if (e->ivex == v)
                cur.edge = e->ilink;
            else
                cur.edge = e->jlink;

            if (e->visited)
                continue;

            e->visited = true;
            int w = graph->getOtherVertex(e, v);

            if (!visited[w])
            {
                // ⭐ 关键：先把“更新后的当前帧”压回去
                S.push(cur);

                parent[w] = v;
                S.push({w, graph->getFirstEdge(w)});

                foundChild = true;
                break;
            }
        }

        // 如果 v 还有边没处理，cur 已经被压回
        // 如果没找到子结点，cur 被自然丢弃（回溯）
        if (!foundChild)
        {
            // 什么都不做，cur 生命周期结束
        }
    }
}


/* ================= 输出接口 ================= */

void DFSStack::printVisitOrder() const
{
    cout << "DFS(Stack) Visit Order: ";
    for (int v : visitOrder)
    {
        cout << v << " ";
    }
    cout << endl;
}

void DFSStack::printTreeEdges() const
{
    cout << "DFS(Stack) Tree Edges:" << endl;
    for (auto& e : treeEdges)
    {
        cout << e.first << " -> " << e.second << endl;
    }
}

/* ================= Getter ================= */

const vector<int>& DFSStack::getVisitOrder() const
{
    return visitOrder;
}

const vector<pair<int,int>>& DFSStack::getTreeEdges() const
{
    return treeEdges;
}
