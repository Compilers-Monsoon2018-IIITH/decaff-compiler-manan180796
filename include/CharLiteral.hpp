#ifndef CharLiteral_hpp
#define CharLiteral_hpp

#include <Literal.hpp>

class CharLiteral : public Literal {
    char data;

  public:
    CharLiteral(char data);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

#endif