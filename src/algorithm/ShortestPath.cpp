#include "ShortestPath.h"

ShortestPath::ShortestPath(GraphAL*g)
{
    graph=g;
}



void ShortestPath::run(int startVertex)
{
    vector<bool>visited(graph->getVexNum()+1,false);
    dist.clear();
    prev.clear();


    prev.assign(graph->getVexNum()+1,-1);
    dist.assign(graph->getVexNum()+1,INF);
    dist[startVertex]=0;

    for(int i=1;i<=graph->getVexNum();i++)
    {
        int u=-1;
        long long minDist=INF;
        for(int v=1;v<=graph->getVexNum();v++)
        {
            if(!visited[v]&&dist[v]<minDist)
            {
                minDist=dist[v];
                u=v;
            }
        }

        if(u==-1)break;//说明剩下点不可达
        visited[u]=true;

        for(GraphAL::EdgeNode*e=graph->getFirstEdge(u);e!=nullptr;e=e->next)
        {
            int w=e->to;
            int weight=e->weight;

            if(!visited[w]&&dist[u]+weight<dist[w])
            {
                dist[w]=dist[u]+weight;//松弛公式
                prev[w]=u;
            }
        }
    }
}


long long ShortestPath::getDistance(int v) const
{
    if (v < 1 || v >= (int)dist.size())
        return INF;
    return dist[v];
}


vector<int> ShortestPath::getPath(int targetVertex) const
{
    vector<int> path;

    // 不可达
    if (targetVertex < 1 ||
        targetVertex >= (int)dist.size() ||
        dist[targetVertex] == INF)
        return path;

    // 反向回溯
    for (int v = targetVertex; v != -1; v = prev[v])
    {
        path.push_back(v);
    }

    // 反转得到 正向路径
    reverse(path.begin(), path.end());
    return path;
}


void ShortestPath::printPath(int targetVertex) const
{
    vector<int> path = getPath(targetVertex);

    cout << "Path to " << targetVertex << ": ";
    if (path.empty())
    {
        cout << "unreachable" << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); i++)
    {
        cout << path[i];
        if (i + 1 < path.size())
            cout << " -> ";
    }
    cout << endl;
}


void ShortestPath::printDistance() const
{
    cout << "Shortest distances:" << endl;
    for (int v = 1; v < (int)dist.size(); v++)
    {
        cout << v << " : ";
        if (dist[v] == INF)
            cout << "INF";
        else
            cout << dist[v];
        cout << endl;
    }
}


