#ifndef UnaryExpression_hpp
#define UnaryExpression_hpp

#include <Expression.hpp>

class UnaryExpression : public Expression {
    friend class LLVMIRGenerator;
};

#endif