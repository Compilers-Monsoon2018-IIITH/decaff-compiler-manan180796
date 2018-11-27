#ifndef Literal_hpp
#define Literal_hpp

#include <UnaryExpression.hpp>

class Literal : public UnaryExpression {
  public:
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    friend class LLVMIRGenerator;
};


#endif