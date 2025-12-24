#ifndef STACK_H
#define STACK_H

#include "../graph/GraphAML.h"

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
    Frame* data;     // 顺序存储的数组
    int top;         // 栈顶指针
    int capacity;    // 栈容量

public:
    explicit Stack(int cap = 1000);  // 构造函数
    ~Stack();                        // 析构函数

    bool isEmpty() const;
    bool isFull() const;

    bool push(const Frame& f);
    bool pop(Frame& f);
    bool peek(Frame& f) const;

    void clear();
};

#endif
