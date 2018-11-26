
#if !defined(ReturnStatement_hpp)
#define ReturnStatement_hpp

#include <Expression.hpp>
#include <Statement.hpp>


class ReturnStatement : public Statement {
  private:
    Expression* expression;

  public:
    ReturnStatement(Expression* expression = nullptr);
    virtual void accept(Visitor* visitor) {visitor->visit(this);}
    ~ReturnStatement();
};


#endif  // ReturnStatement_hpp
