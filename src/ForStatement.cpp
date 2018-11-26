
#if !defined(ForStatement_cpp)
#define ForStatement_cpp

#include <ForStatement.hpp>


ForStatement::ForStatement(std::string variable_name, Expression* start,
                           Expression* end, Block* block)
    : variable_name(variable_name), start(start), end(end), block(block) {}

ForStatement::~ForStatement() {
    if (start) delete start;
    if (end) delete end;
    if (block) delete block;
}


#endif  // ForStatement_cpp
