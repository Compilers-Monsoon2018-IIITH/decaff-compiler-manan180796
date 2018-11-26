#if !defined(UnaryOperation_cpp)
#define UnaryOperation_cpp

#include <UnaryOperation.hpp>

UnaryOperation::UnaryOperation(std::string op, Expression* exp)
    : op(op), exp(exp) {}

UnaryOperation::~UnaryOperation() {}

#endif  // UnaryOperation_cpp