#ifndef IntLiteral_hpp
#define IntLiteral_hpp

#include <Literal.hpp>

class IntLiteral : public Literal {
    int data;

  public:
    IntLiteral(int data);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

#endif