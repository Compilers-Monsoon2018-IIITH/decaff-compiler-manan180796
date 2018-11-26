
#if !defined(MethodDeclaration_cpp)
#define MethodDeclaration_cpp

#include <MethodDeclaration.hpp>


MethodDeclaration::MethodDeclaration(Types retutn_type, std::string name,
                                     ArgumentDeclarationList* arg_list,
                                     Block* body)
    : return_type(retutn_type), name(name), arg_list(arg_list), body(body) {}

MethodDeclaration::~MethodDeclaration() {
    if (arg_list != nullptr) delete arg_list;
    delete body;
}


#endif  // MethodDeclaration_cpp
