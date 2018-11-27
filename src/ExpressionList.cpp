
#if !defined(ExpressionList_cpp)
#define ExpressionList_cpp

#include <ExpressionList.hpp>

ExpressionList::ExpressionList() {}
void ExpressionList::AddExpression(Expression* expression) {
    exp_list.push_back(expression);
}
void ExpressionList::accept(Visitor* visitor) { visitor->visit(this); }
std::vector<Expression*> ExpressionList::GetList() { return this->exp_list; }

#endif  // ExpressionList_cpp
