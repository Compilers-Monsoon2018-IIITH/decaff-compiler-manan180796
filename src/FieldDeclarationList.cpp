#if !defined(FieldDeclarationList_cpp)
#define FieldDeclarationList_cpp

#include <FieldDeclarationList.hpp>

FieldDeclarationList::FieldDeclarationList(/* args */) {}
void FieldDeclarationList::AddDeclaration(FieldDeclaration* decl) {
    decl_list.push_back(decl);
}

FieldDeclarationList::~FieldDeclarationList() {
    for (auto decl : decl_list) delete decl;
}


#endif  // FieldDeclarationList_cpp