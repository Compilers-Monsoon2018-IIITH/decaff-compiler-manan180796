
#if !defined(VariableDeclaration_cpp)
#define VariableDeclaration_cpp

#include <VariableDeclaration.hpp>


VariableDeclaration::VariableDeclaration(Types type, IdList* id_list)
    : type(type), id_list(id_list) {}

VariableDeclaration::~VariableDeclaration() {}

#endif  // VariableDeclaration_cpp
