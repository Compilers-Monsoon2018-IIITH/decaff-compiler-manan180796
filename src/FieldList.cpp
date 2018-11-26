
#if !defined(FieldList_cpp)
#define FieldList_cpp

#include <FieldList.hpp>

FieldList::FieldList(/* args */) {}
void FieldList::AddField(Field *field) { field_list.push_back(field); }

FieldList::~FieldList() {
    for (auto field : field_list) delete field;
}

#endif  // FieldList_cpp
