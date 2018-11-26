
#if !defined(MethodDeclarationList_cpp)
#define MethodDeclarationList_cpp

#include <MethodDeclarationList.hpp>


MethodDeclarationList::MethodDeclarationList() {}
void MethodDeclarationList::AddDeclaration(MethodDeclaration* decl) {
    decl_list.push_back(decl);
}

MethodDeclarationList::~MethodDeclarationList() {
    for (auto decl : decl_list) delete decl;
}
#endif  // MethodDeclarationList_cpp
