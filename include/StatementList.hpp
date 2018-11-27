
#if !defined(StatementList_hpp)
#define StatementList_hpp

#include <AstNode.hpp>
#include <Statement.hpp>
#include <vector>


class StatementList : public AstNode {
  private:
    std::vector<Statement*> statements;

  public:
    StatementList();
    void AddStatement(Statement* statement);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~StatementList();
    friend class LLVMIRGenerator;
};


#endif  // StatementList_hpp
