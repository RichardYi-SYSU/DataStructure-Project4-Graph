#ifndef TREE_BUILDER_H
#define TREE_BUILDER_H

#include <vector>
#include <utility>
#include <iostream>

#include "../graph/GraphAL.h"

using namespace std;

/**
 TreeBuilder
 根据遍历得到的“生成树边集”，构造一棵树（邻接表表示）
 */
class TreeBuilder {
private:
    GraphAL* tree;   // 生成树（邻接表形式）

public:
    // 构造函数：指定树的顶点数
    TreeBuilder(int vertexCount);

    // 析构函数
    ~TreeBuilder();

    /**
     * 根据边集构造树
     * @param edges 生成树边集 (u, v)
     * @param directed 是否构造为有向树（默认 true）
     */
    void buildFromEdges(const vector<pair<int,int>>& edges,
                        bool directed = true);

    // 获取生成树
    GraphAL* getTree() const;

    // 输出树结构
    void printTree() const;

    void printTreeAsHierarchy(int root)const;

    void printSubTree(int v, int depth) const;
    
    
};

#endif
