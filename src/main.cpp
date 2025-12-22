#include <iostream>
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

            DFSStack dfs(amlGraph);
            dfs.run(start);

            TreeBuilder builder(amlGraph->getVexNum());
            builder.buildFromEdges(dfs.getTreeEdges(), true);
            //cout << "DFS 生成树（有向邻接表）：" << endl;
            builder.printTreeAsHierarchy(start);
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
            //cout << "BFS 生成树（有向邻接表）：" << endl;
            builder.printTreeAsHierarchy(start);
            break;
        }

        /* ---------- 最短路径（Dijkstra） ---------- */
        case 7:
        {
            if (alGraph) delete alGraph;

            cout << "请输入顶点数和边数：";
            cin >> n >> m;

            alGraph = new GraphAL(n);

            cout << "请输入每条有向边（起点 终点 权值）：\n";
            for (int i = 0; i < m; i++)
            {
                int u, v, w;
                cin >> u >> v >> w;
                alGraph->addEdge(u, v, w);
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
