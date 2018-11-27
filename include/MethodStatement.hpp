
#if !defined(MethodStatement_hpp)
#define MethodStatement_hpp

#include <MethodCall.hpp>
#include <Statement.hpp>


class MethodStatement : public Statement {
  private:
    MethodCall* call;

  public:
    MethodStatement(MethodCall* call);
    ~MethodStatement();
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    friend class LLVMIRGenerator;
};


#endif  // MethodStatement_hpp
