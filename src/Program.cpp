#if !defined(Program_cpp)
#define Program_cpp

#include <Program.hpp>

Program::Program(FieldDeclarationList* field_list,
                 MethodDeclarationList* method_list)
    : field_list(field_list), method_list(method_list) {}

Program::~Program() {
    if (field_list != nullptr) delete field_list;
    if (method_list != nullptr) delete method_list;
}

#endif  // Program_cpp