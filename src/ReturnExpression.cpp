
#if !defined(ReturnExpression_cpp)
#define ReturnExpression_cpp

#include <ReturnStatement.hpp>

ReturnStatement::ReturnStatement(Expression* expression)
    : expression(expression) {}

ReturnStatement::~ReturnStatement() {
    if (expression != nullptr) delete expression;
}


#endif  // ReturnExpression_cpp
