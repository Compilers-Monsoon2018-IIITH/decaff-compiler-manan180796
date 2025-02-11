#if !defined(SimpleMethod_cpp)
#define SimpleMethod_cpp

#include <SimpleMethod.hpp>

SimpleMethod::SimpleMethod(std::string name, ExpressionList* argument_list)
    : method_name(name), argument_list(argument_list) {
    if (argument_list == nullptr) {
        this->argument_list = new ExpressionList();
    }
}

#endif  // SimpleMethod_cpp
