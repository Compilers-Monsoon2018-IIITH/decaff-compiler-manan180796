#ifndef Expression_hpp
#define Expression_hpp

#include <AstNode.hpp>

class Expression : public AstNode {
  protected:
  public:
    virtual bool IsLocation();
    virtual void accept(Visitor* visitor);
    friend class LLVMIRGenerator;
};


#endif