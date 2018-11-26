#if !defined(FieldDeclaration_cpp)
#define FieldDeclaration_cpp

#include <FieldDeclaration.hpp>


FieldDeclaration::FieldDeclaration(Types type, FieldList* field_list)
    : type(type), field_list(field_list) {}

FieldDeclaration::~FieldDeclaration() { delete field_list; }

#endif  // FieldDeclaration_cpp