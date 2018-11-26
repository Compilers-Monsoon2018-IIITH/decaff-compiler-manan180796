#ifndef MethodCall_hpp
#define MethodCall_hpp

#include <UnaryExpression.hpp>

class MethodCall : public UnaryExpression {
  public:
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};

#endif