#if !defined(BoolLiteral_hpp)
#define BoolLiteral_hpp


#include <Literal.hpp>

class BoolLiteral : public Literal {
    bool data;

  public:
    BoolLiteral(bool data);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

#endif  // BoolLiteral_hpp