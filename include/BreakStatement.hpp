
#if !defined(BreakStatement_hpp)
#define BreakStatement_hpp

#include <Statement.hpp>


class BreakStatement : public Statement {
  private:
    /* data */
  public:
    BreakStatement(/* args */);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~BreakStatement();
    friend class LLVMIRGenerator;
};


#endif  // BreakStatement_hpp
