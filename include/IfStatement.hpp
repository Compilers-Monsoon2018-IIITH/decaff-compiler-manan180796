
#if !defined(IfStatement_hpp)
#define IfStatement_hpp

#include <Block.hpp>
#include <Expression.hpp>
#include <Statement.hpp>


class IfStatement : public Statement {
  private:
    Expression* exp;
    Block* if_block;
    Block* else_block;

  public:
    IfStatement(Expression* exp, Block* if_block, Block* else_block = nullptr);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~IfStatement();
};


#endif  // IfStatement_hpp
