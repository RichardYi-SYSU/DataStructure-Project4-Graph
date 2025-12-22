#include "BFS.h"

BFS::BFS(GraphAML*g)
{
    graph=g;
}

void BFS::run(int startVertex)
{
    // 1. 初始化 visited（大小 = 顶点数 + 1）
    visited.assign(graph->getVexNum()+1,false);

    // 2. 清空访问序列和生成树边集
    visitOrder.clear();
    treeEdges.clear();

    // 3. 重置图中所有边的 visited 标志
    graph->resetEdgeVisited();

    queue<int>Q;

    visited[startVertex]=true;
    Q.push(startVertex);


    while(!Q.empty())
    {
        int v=Q.front();Q.pop();

        visitOrder.push_back(v);

        for(GraphAML::EdgeNode*e=graph->getFirstEdge(v);e!=nullptr;)
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

            e->visited=true;

            int w=graph->getOtherVertex(e,v);
            
            if(!visited[w])
            {
                visited[w]=true;
                treeEdges.emplace_back(v,w);
                Q.push(w);
            }

            if(e->ivex==v)
            {
                e=e->ilink;
            }else{
                e=e->jlink;
            }
        }
    }
}


/* ================= 输出接口 ================= */

void BFS::printVisitOrder() const
{
    cout << "BFS Visit Order: ";
    for (int v : visitOrder) {
        cout << v << " ";
    }
    cout << endl;
}

void BFS::printTreeEdges() const
{
    cout << "BFS Tree Edges:" << endl;
    for (auto& e : treeEdges) {
        cout << e.first << " -> " << e.second << endl;
    }
}

/* ================= Getter ================= */

const vector<int>& BFS::getVisitOrder() const
{
    return visitOrder;
}

const vector<pair<int,int>>& BFS::getTreeEdges() const
{
    return treeEdges;
}

