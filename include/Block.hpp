
#if !defined(Block_hpp)
#define Block_hpp

#include <Statement.hpp>
#include <StatementList.hpp>
#include <VariableDeclarationList.hpp>


class Block : public Statement {
  private:
    VariableDeclarationList* var_list;
    StatementList* statement_list;

  public:
    Block(VariableDeclarationList* var_list, StatementList* statement_list);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~Block();
};


#endif  // Block_hpp
