
#if !defined(ExpressionList_cpp)
#define ExpressionList_cpp

#include <ExpressionList.hpp>

ExpressionList::ExpressionList() {}
void ExpressionList::AddExpression(Expression* expression) {
    exp_list.push_back(expression);
}

#endif  // ExpressionList_cpp
