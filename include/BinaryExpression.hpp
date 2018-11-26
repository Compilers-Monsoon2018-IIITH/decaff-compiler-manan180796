#if !defined(BinaryExpression_hpp)
#define BinaryExpression_hpp


#include <Expression.hpp>
#include <string>

class BinaryExpression : public Expression {
    Expression *left_operand;
    std::string op;
    Expression *right_operand;

  public:
    BinaryExpression(Expression *left_operand, std::string op,
                     Expression *right_operand);
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
};

#endif  // BinaryExpression_hpp
