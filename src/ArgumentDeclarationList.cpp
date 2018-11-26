
#if !defined(ArgumentDeclarationList_cpp)
#define ArgumentDeclarationList_cpp
#include <ArgumentDeclarationList.hpp>

ArgumentDeclarationList::ArgumentDeclarationList() {}
void ArgumentDeclarationList::AddArgument(ArgumentDeclaration* arg) {
    arg_list.push_back(arg);
}

ArgumentDeclarationList::~ArgumentDeclarationList() {}

#endif  // ArgumentDeclarationList_cpp
