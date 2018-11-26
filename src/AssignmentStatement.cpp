#if !defined(AssignmentStatement_cpp)
#define AssignmentStatement_cpp

#include <AssignmentStatement.hpp>

AssignmentStatement::AssignmentStatement(Location* location,
                                         std::string assignment_op,
                                         Expression* expression)
    : location(location),
      assignment_op(assignment_op),
      expression(expression) {}
#endif  // AssignmentStatement_cpp
