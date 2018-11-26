
#if !defined(CalloutMethod_cpp)
#define CalloutMethod_cpp

#include <CalloutMethod.hpp>

CalloutMethod::CalloutMethod(std::string method_name, CalloutArgList* arg_list)
    : method_name(method_name), arg_list(arg_list) {}


#endif  // CalloutMethod_cpp
