#if !defined(Expression_cpp)
#define Expression_cpp

#include <Expression.hpp>

bool Expression::IsLocation() { return false; }

inline void Expression::accept(Visitor* visitor) { visitor->visit(this); }


#endif  // Expression_cpp