
#if !defined(Block_cpp)
#define Block_cpp

#include <Block.hpp>


Block::Block(VariableDeclarationList* var_list, StatementList* statement_list)
    : var_list(var_list), statement_list(statement_list) {}

Block::~Block() {
    if (var_list) delete var_list;
    if (statement_list) delete statement_list;
}

#endif  // Block_cpp
