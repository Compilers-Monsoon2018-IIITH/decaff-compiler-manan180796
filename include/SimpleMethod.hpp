#ifndef SimpleMethod_hpp
#define SimpleMethod_hpp

#include <ExpressionList.hpp>
#include <MethodCall.hpp>
#include <string>


class SimpleMethod : public MethodCall {
    std::string method_name;
    ExpressionList* argument_list;

  public:
    SimpleMethod(std::string name, ExpressionList* argument_list = nullptr);
    virtual void accept(Visitor* visitor) {visitor->visit(this);}
};

#endif