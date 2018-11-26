
#if !defined(ArgumentDelarationList_hpp)
#define ArgumentDelarationList_hpp

#include <ArgumentDeclaration.hpp>
#include <AstNode.hpp>
#include <vector>

class ArgumentDeclarationList : public AstNode {
  private:
    std::vector<ArgumentDeclaration*> arg_list;

  public:
    ArgumentDeclarationList();
    void AddArgument(ArgumentDeclaration* arg);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~ArgumentDeclarationList();
};


#endif  // ArgumentDelarationList_hpp
