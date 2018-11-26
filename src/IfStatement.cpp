
#if !defined(IfStatement_cpp)
#define IfStatement_cpp

#include <IfStatement.hpp>


IfStatement::IfStatement(Expression* exp, Block* if_block, Block* else_block)
    : exp(exp), if_block(if_block), else_block(else_block) {}

IfStatement::~IfStatement() {
    delete this->exp;
    delete if_block;
    if (else_block != nullptr) delete else_block;
}

#endif  // IfStatement_cpp
