#if !defined(CalloutArg_hpp)
#define CalloutArg_hpp


#include <AstNode.hpp>
#include <Expression.hpp>
#include <string>
class CalloutArg : public AstNode {
    Expression* argument;
    std::string str_arg;

  public:
    CalloutArg(Expression* argument);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    CalloutArg(std::string str_arg);
};

#endif  // CalloutArg_hpp