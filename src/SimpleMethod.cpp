#if !defined(SimpleMethod_cpp)
#define SimpleMethod_cpp

#include <SimpleMethod.hpp>

SimpleMethod::SimpleMethod(std::string name, ExpressionList* argument_list)
    : method_name(name), argument_list(argument_list) {}

#endif  // SimpleMethod_cpp
