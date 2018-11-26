
#if !defined(VariableDeclarationList_cpp)
#define VariableDeclarationList_cpp

#include <VariableDeclarationList.hpp>


VariableDeclarationList::VariableDeclarationList() : var_list() {}
void VariableDeclarationList::AddDeclaration(VariableDeclaration* declaration) {
    var_list.push_back(declaration);
}

VariableDeclarationList::~VariableDeclarationList() {
    for (auto declaration : var_list) delete declaration;
}


#endif  // VariableDeclarationList_cpp
