#ifndef ExpressionList_hpp
#define ExpressionList_hpp

#include <Expression.hpp>
#include <vector>
class ExpressionList : public AstNode {
    std::vector<Expression*> exp_list;

  public:
    ExpressionList();
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    void AddExpression(Expression* expression);
};

#endif