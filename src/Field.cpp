
#if !defined(Field_cpp)
#define Field_cpp

#include <Field.hpp>

Field::Field(std::string name, IntLiteral* size) : name(name), size(size) {}

Field::~Field() {
    if (size != nullptr) delete size;
}


#endif  // Field_cpp
