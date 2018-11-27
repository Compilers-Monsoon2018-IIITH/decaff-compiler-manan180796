#ifndef Location_hpp
#define Location_hpp

#include <UnaryExpression.hpp>
#include <string>

class Location : public UnaryExpression {
    std::string var_name;
    Expression *index;

  public:
    Location(std::string var_name, Expression *index = nullptr);
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
    virtual bool IsLocation() override;
    friend class LLVMIRGenerator;
};

#endif