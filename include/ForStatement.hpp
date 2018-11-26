
#if !defined(ForStatement_hpp)
#define ForStatement_hpp

#include <Block.hpp>
#include <Expression.hpp>
#include <Statement.hpp>
#include <string>

class ForStatement : public Statement {
  private:
    std::string variable_name;
    Expression* start;
    Expression* end;
    Block* block;

  public:
    ForStatement(std::string variable_name, Expression* start, Expression* end,
                 Block* block);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~ForStatement();
};


#endif  // ForStatement_hpp