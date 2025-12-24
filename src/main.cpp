#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <windows.h>
using namespace std;

/* ================= 图结构 ================= */
#include "graph/GraphAML.h"
#include "graph/GraphAL.h"

/* ================= 遍历算法 ================= */
#include "algorithm/DFS.h"
#include "algorithm/DFSStack.h"
#include "algorithm/BFS.h"

/* ================= 生成树 ================= */
#include "algorithm/TreeBuilder.h"

/* ================= 最短路径 ================= */
#include "algorithm/ShortestPath.h"

/* ================= 菜单显示 ================= */

void showMenu()
{
    cout << "\n========== Project 4：图结构与图算法 ==========\n";
    cout << "1. 建立无向图（邻接多重表）\n";
    cout << "2. 深度优先遍历 DFS（递归）\n";
    cout << "3. 深度优先遍历 DFS（非递归，栈实现）\n";
    cout << "4. 广度优先遍历 BFS\n";
    cout << "5. 构造 DFS 生成树\n";
    cout << "6. 构造 BFS 生成树\n";
    cout << "7. 最短路径（Dijkstra 算法）\n";
    cout << "0. 退出程序\n";
    cout << "=============================================\n";
    cout << "请选择操作：";
}


//生成Graphviz可视化Dot文件
static void writeTreeDot(const string& path,
                         int vertexCount,
                         const vector<pair<int, int>>& edges,
                         bool directed)
{
    ofstream out(path);
    if (!out)
    {
        cout << "Dot 文件写入失败：" << path << endl;
        return;
    }

    out << (directed ? "digraph" : "graph") << " Tree {\n";
    out << "  node [shape=circle];\n";

    for (int i = 1; i <= vertexCount; ++i)
    {
        out << "  " << i << ";\n";
    }

    const char* link = directed ? " -> " : " -- ";
    for (const auto& e : edges)
    {
        out << "  " << e.first << link << e.second << ";\n";
    }
    out << "}\n";
}

/* ================= 主函数 ================= */
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    GraphAML* amlGraph = nullptr;   // 无向图（邻接多重表）
    GraphAL*  alGraph  = nullptr;   // 有向带权图（邻接表）

    int choice;
    int n, m;

    while (true)
    {
        showMenu();
        cin >> choice;

        if (choice == 0)
        {
            cout << "程序结束，已退出。\n";
            break;
        }

        switch (choice)
        {
        /* ---------- 建立无向图（AML） ---------- */
        case 1:
        {
            if (amlGraph) delete amlGraph;

            cout << "请输入顶点数和边数：";
            cin >> n >> m;

            amlGraph = new GraphAML(n);

            cout << "请输入每条边的两个端点（u v）：\n";
            for (int i = 0; i < m; i++)
            {
                int u, v;
                cin >> u >> v;
                amlGraph->addEdge(u, v);
            }

            cout << "无向图建立完成。\n";
            amlGraph->print();
            break;
        }

        /* ---------- 递归 DFS ---------- */
        case 2:
        {
            if (!amlGraph)
            {
                cout << "请先建立无向图。\n";
                break;
            }

            int start;
            cout << "请输入起始顶点：";
            cin >> start;

            DFS dfs(amlGraph);
            dfs.run(start);
            dfs.printVisitOrder();
            dfs.printTreeEdges();
            break;
        }

        /* ---------- 非递归 DFS ---------- */
        case 3:
        {
            if (!amlGraph)
            {
                cout << "请先建立无向图。\n";
                break;
            }

            int start;
            cout << "请输入起始顶点：";
            cin >> start;

            DFSStack dfsStack(amlGraph);
            dfsStack.run(start);
            dfsStack.printVisitOrder();
            dfsStack.printTreeEdges();
            break;
        }

        /* ---------- BFS ---------- */
        case 4:
        {
            if (!amlGraph)
            {
                cout << "请先建立无向图。\n";
                break;
            }

            int start;
            cout << "请输入起始顶点：";
            cin >> start;

            BFS bfs(amlGraph);
            bfs.run(start);
            bfs.printVisitOrder();
            bfs.printTreeEdges();
            break;
        }

        /* ---------- DFS 生成树 ---------- */
        case 5:
        {
            if (!amlGraph)
            {
                cout << "请先建立无向图。\n";
                break;
            }

            int start;
            cout << "请输入起始顶点：";
            cin >> start;

            DFSStack dfsStack(amlGraph);
            dfsStack.run(start);

            TreeBuilder builder(amlGraph->getVexNum());
            builder.buildFromEdges(dfsStack.getTreeEdges(), true);
            cout << "DFS 生成树（有向邻接表）：" << endl;
            builder.printTree();
            cout<<endl;
            cout<<"DFS 生成树（树形输出）"<<endl;
            builder.printTreeAsHierarchy(start);

            string dotPath;
            cout << "请输入 DFS 生成树 Dot 文件路径（例如 data/dfs_tree.dot）：";
            cin >> dotPath;
            writeTreeDot(dotPath,
                         amlGraph->getVexNum(),
                         dfsStack.getTreeEdges(),
                         true);
            break;
        }

        /* ---------- BFS 生成树 ---------- */
        case 6:
        {
            if (!amlGraph)
            {
                cout << "请先建立无向图。\n";
                break;
            }

            int start;
            cout << "请输入起始顶点：";
            cin >> start;

            BFS bfs(amlGraph);
            bfs.run(start);

            TreeBuilder builder(amlGraph->getVexNum());
            builder.buildFromEdges(bfs.getTreeEdges(), true);
            cout << "BFS 生成树（有向邻接表）：" << endl;
            builder.printTree();
            cout<<endl;
            cout<<"BFS 生成树（树形输出）"<<endl;
            builder.printTreeAsHierarchy(start);

            string dotPath;
            cout << "请输入 BFS 生成树 Dot 文件路径（例如 data/bfs_tree.dot）：";
            cin >> dotPath;
            writeTreeDot(dotPath,
                         amlGraph->getVexNum(),
                         bfs.getTreeEdges(),
                         true);
            break;
        }

        /* ---------- 最短路径（Dijkstra） ---------- */
        case 7:
        {
            if (alGraph) delete alGraph;

            cout << "请输入顶点数和边数：";
            cin >> n >> m;

            alGraph = new GraphAL(n);

            cout << "建立无向图输入1，建立有向图输入0：\n";
            int sw;
            cin>>sw;
            if(sw==1)
            {
                cout<<"请依次输入每条边的两个点、权值（不重复）";
                for (int i = 0; i < m; i++)
                {
                    int u, v, w;
                    cin >> u >> v >> w;
                    alGraph->addEdge(u, v, w);
                    alGraph->addEdge(v, u, w);
                }
            }else{
                cout<<"请依次输入起点、终点、权值";
                for (int i = 0; i < m; i++)
                {
                    int u, v, w;
                    cin >> u >> v >> w;
                    alGraph->addEdge(u, v, w);
                }
            }
            

            int start;
            cout << "请输入最短路径的起始顶点：";
            cin >> start;

            ShortestPath sp(alGraph);
            sp.run(start);
            sp.printDistance();

            int target;
            cout << "请输入要查询路径的目标顶点：";
            cin >> target;
            sp.printPath(target);
            break;
        }

        default:
            cout << "无效的选项，请重新输入。\n";
        }
    }

    /* ---------- 释放资源 ---------- */
    delete amlGraph;
    delete alGraph;

    return 0;
}
