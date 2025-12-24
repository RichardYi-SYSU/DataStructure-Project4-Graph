#include "TreeBuilder.h"

#include "TreeBuilder.h"

/* ================= 构造与析构 ================= */

TreeBuilder::TreeBuilder(int vertexCount)
{
    // 创建一棵空树（邻接表）
    tree = new GraphAL(vertexCount);
}

TreeBuilder::~TreeBuilder()
{
    delete tree;
}

/* ================= 构造生成树 ================= */

void TreeBuilder::buildFromEdges(const vector<pair<int,int>>& edges,
                                 bool directed)
{
    // 根据生成树边集逐条加入边
    for (const auto& e : edges)
    {
        int u = e.first;
        int v = e.second;

        // 加入 u -> v
        tree->addEdge(u, v);

        // 如果是无向树，再加一条反向边
        if (!directed)
        {
            tree->addEdge(v, u);
        }
    }
}

/* ================= Getter ================= */

GraphAL* TreeBuilder::getTree() const
{
    return tree;
}

/* ================= 输出 ================= */

void TreeBuilder::printTree() const
{
    cout << "Generated Tree (Adjacency List):" << endl;
    tree->print();
}

void TreeBuilder::printTreeAsHierarchy(int root) const
{
    cout << "Tree Structure:" << endl;
    printSubTree(root, 0);
}

void TreeBuilder::printSubTree(int v, int depth) const
{
    // 缩进
    for (int i = 0; i < depth; i++)
        cout << "  ";

    cout << v << endl;

    // 遍历 v 的所有子结点
    for (GraphAL::EdgeNode* e = tree->getFirstEdge(v);
         e != nullptr;
         e = e->next)
    {
        int child = e->to;
        printSubTree(child, depth + 1);
    }
}

