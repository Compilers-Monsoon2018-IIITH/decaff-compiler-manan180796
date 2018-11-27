#if !defined(Statement_hpp)
#define Statement_hpp

#include <AstNode.hpp>


class Statement : public AstNode {
  public:
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    friend class LLVMIRGenerator;
};

#endif  // Statement_hpp
