#if !defined(AstNode_hpp)
#define AstNode_hpp


#include <Visitor.hpp>

class AstNode {
  public:
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

#endif  // AstNode_hpp