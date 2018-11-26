#if !defined(StatementList_cpp)
#define StatementList_cpp

#include <StatementList.hpp>

StatementList::StatementList(/* args */) : statements() {}
void StatementList::AddStatement(Statement* statement) {
    statements.push_back(statement);
}

StatementList::~StatementList() {}


#endif  // StatementList_cpp