
#if !defined(Location_cpp)
#define Location_cpp

#include <Location.hpp>

Location::Location(std::string var_name, Expression *index)
    : var_name(var_name), index(index) {}
bool Location::IsLocation() { return index == nullptr; }

#endif  // Location_cpp
