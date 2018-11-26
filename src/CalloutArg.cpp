#ifndef CalloutArg_cpp
#define CalloutArg_cpp

#include <CalloutArg.hpp>

CalloutArg::CalloutArg(Expression* argument)
    : argument(argument), str_arg("") {}
CalloutArg::CalloutArg(std::string str_arg)
    : argument(nullptr), str_arg(str_arg) {}

#endif