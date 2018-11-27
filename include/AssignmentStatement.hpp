#if !defined(AssignmentStatement_hpp)
#define AssignmentStatement_hpp

#include <Expression.hpp>
#include <Location.hpp>
#include <Statement.hpp>
#include <string>

class AssignmentStatement : public Statement {
  public:
    Location* location;
    std::string assignment_op;
    Expression* expression;


    AssignmentStatement(Location* location, std::string assignment_op,
                        Expression* expression);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    friend class LLVMIRGenerator;
};

#endif  // AssignmentStatement_hpp
