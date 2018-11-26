#if !defined(NestedUnaryExpression_hpp)
#define NestedUnaryExpression_hpp

#include <Expression.hpp>
#include <UnaryExpression.hpp>

class NestedUnaryExpression : public UnaryExpression {
  private:
    Expression* exp;

  public:
    NestedUnaryExpression(Expression* exp);
    virtual void accept(Visitor* visitor) {visitor->visit(this);}
    ~NestedUnaryExpression();
};


#endif  // NestedUnaryExpression_hpp