
#if !defined(ArgumentDeclaration_cpp)
#define ArgumentDeclaration_cpp

#include <ArgumentDeclaration.hpp>

ArgumentDeclaration::ArgumentDeclaration(Types type, std::string arg_name)
    : type(type), arg_name(arg_name) {}

ArgumentDeclaration::~ArgumentDeclaration() {}


#endif  // ArgumentDeclaration_cpp
