#ifndef Expression_hpp
#define Expression_hpp

#include <AstNode.hpp>

class Expression : public AstNode {
  public:
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};


#endif