
#if !defined(MethodStatement_cpp)
#define MethodStatement_cpp

#include <MethodStatement.hpp>


MethodStatement::MethodStatement(MethodCall* call) : call(call) {}

MethodStatement::~MethodStatement() { delete call; }


#endif  // MethodStatement_cpp
