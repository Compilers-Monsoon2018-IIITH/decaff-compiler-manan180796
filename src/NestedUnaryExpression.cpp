#if !defined(NestedUnaryExpression_cpp)
#define NestedUnaryExpression_cpp

#include <NestedUnaryExpression.hpp>


NestedUnaryExpression::NestedUnaryExpression(Expression* exp) : exp(exp) {}

NestedUnaryExpression::~NestedUnaryExpression() {}

bool NestedUnaryExpression::IsLocation() { return this->exp->IsLocation(); }

#endif  // NestedUnaryExpression_cpp