#include "Stack.h"

bool Stack::isEmpty() const
{
    return data.empty();
}

void Stack::push(const Frame& f)
{
    data.push_back(f);
}

bool Stack::pop(Frame& f)
{
    if (data.empty()) return false;
    f = data.back();
    data.pop_back();
    return true;
}

bool Stack::peek(Frame& f) const
{
    if (data.empty()) return false;
    f = data.back();
    return true;
}

void Stack::clear()
{
    data.clear();
}
