#include "DFS.h"

/* ================= 构造函数 ================= */

DFS::DFS(GraphAML* g)
{
    graph = g;
}

/* ================= 对外接口 ================= */

void DFS::run(int startVertex)
{
    // 1. 初始化 visited（大小 = 顶点数 + 1）
    visited.assign(graph->getVexNum()+1,false);

    // 2. 清空访问序列和生成树边集
    visitOrder.clear();
    treeEdges.clear();

    // 3. 重置图中所有边的 visited 标志
    graph->resetEdgeVisited();

    // 4. 从起始顶点开始 DFS
    dfs(startVertex);

}

/* ================= 递归 DFS 核心 ================= */

void DFS::dfs(int v)
{
    // 1. 标记顶点 v 已访问
    visited[v]=true;

    // 2. 添加至访问序列
    visitOrder.push_back(v);

    // 3. 遍历 v 的所有关联边
    for (GraphAML::EdgeNode* e = graph->getFirstEdge(v);e != nullptr;)
    {
        if(e->visited)
        {
            //去到下一条边
            if(e->ivex==v)
            {
                e=e->ilink;
            }else{
                e=e->jlink;
            }
            continue;
        }

        e->visited=true;//标记当前边已访问

        int w=graph->getOtherVertex(e,v);//找到这条边的另一个端点
        
        if(!visited[w])
        {
            treeEdges.emplace_back(v,w);//添加至树边
            dfs(w);
        }

        //去下一条边
        if(e->ivex==v)
        {
            e=e->ilink;
        }else{
            e=e->jlink;
        }


    }
}

/* ================= 输出接口 ================= */

void DFS::printVisitOrder() const
{
    cout << "DFS Visit Order: ";
    for (int v : visitOrder) {
        cout << v << " ";
    }
    cout << endl;
}

void DFS::printTreeEdges() const
{
    cout << "DFS Tree Edges:" << endl;
    for (auto& e : treeEdges) {
        cout << e.first << " -> " << e.second << endl;
    }
}

/* ================= Getter ================= */

const vector<int>& DFS::getVisitOrder() const
{
    return visitOrder;
}

const vector<pair<int,int>>& DFS::getTreeEdges() const
{
    return treeEdges;
}
