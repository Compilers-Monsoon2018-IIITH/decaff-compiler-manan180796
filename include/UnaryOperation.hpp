#if !defined(UnaryOperation_hpp)
#define UnaryOperation_hpp

#include <Expression.hpp>
#include <UnaryExpression.hpp>
#include <string>

class UnaryOperation : public UnaryExpression {
  private:
    std::string op;
    Expression* exp;

  public:
    UnaryOperation(std::string op, Expression* exp);
    virtual void accept(Visitor* visitor) {visitor->visit(this);}
    ~UnaryOperation();
};


#endif  // UnaryOperation_hpp