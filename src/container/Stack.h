#ifndef STACK_H
#define STACK_H

#include <vector>
#include "../graph/GraphAML.h"

using namespace std;

/**
 * 用于非递归 DFS 的栈帧
 * 模拟递归调用栈
 */
struct Frame {
    int v;                           // 当前顶点
    GraphAML::EdgeNode* edge;        // 当前遍历到的边
};

class Stack {
private:
    vector<Frame> data;

public:
    Stack() = default;

    bool isEmpty() const;

    void push(const Frame& f);

    bool pop(Frame& f);

    bool peek(Frame& f) const;

    void clear();
};

#endif
