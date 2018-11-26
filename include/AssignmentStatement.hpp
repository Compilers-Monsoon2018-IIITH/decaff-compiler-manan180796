#if !defined(AssignmentStatement_hpp)
#define AssignmentStatement_hpp

#include <Expression.hpp>
#include <Location.hpp>
#include <Statement.hpp>
#include <string>

class AssignmentStatement : public Statement {
  private:
    Location* location;
    std::string assignment_op;
    Expression* expression;

  public:
    AssignmentStatement(Location* location, std::string assignment_op,
                        Expression* expression);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

#endif  // AssignmentStatement_hpp
