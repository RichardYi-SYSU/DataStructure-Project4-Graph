#include "Stack.h"

/**
 * 构造函数
 */
Stack::Stack(int cap)
{
    capacity = cap;
    data = new Frame[capacity];
    top = -1;
}

/**
 * 析构函数
 */
Stack::~Stack()
{
    delete[] data;
}

bool Stack::isEmpty() const
{
    return top == -1;
}

bool Stack::isFull() const
{
    return top == capacity - 1;
}

bool Stack::push(const Frame& f)
{
    if (isFull()) return false;
    data[++top] = f;
    return true;
}

bool Stack::pop(Frame& f)
{
    if (isEmpty()) return false;
    f = data[top--];
    return true;
}

bool Stack::peek(Frame& f) const
{
    if (isEmpty()) return false;
    f = data[top];
    return true;
}

void Stack::clear()
{
    top = -1;
}
