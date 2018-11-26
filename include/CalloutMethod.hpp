#if !defined(CalloutMethod_hpp)
#define CalloutMethod_hpp


#include <CalloutArgList.hpp>
#include <MethodCall.hpp>
#include <string>

class CalloutMethod : public MethodCall {
    std::string method_name;
    CalloutArgList* arg_list;

  public:
    CalloutMethod(std::string method_name, CalloutArgList* arg_list = nullptr);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~CalloutMethod();
};

#endif  // CalloutMethod_hpp