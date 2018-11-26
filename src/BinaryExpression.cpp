#ifndef BinaryExpression_cpp
#define BinaryExpression_cpp

#include <BinaryExpression.hpp>

BinaryExpression::BinaryExpression(Expression *left_operand, std::string op,
                                   Expression *right_operand)
    : left_operand(left_operand), op(op), right_operand(right_operand) {}

#endif