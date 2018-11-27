
#if !defined(VariableDelarationList_hpp)
#define VariableDelarationList_hpp

#include <AstNode.hpp>
#include <VariableDeclaration.hpp>
#include <vector>

class VariableDeclarationList : public AstNode {
  private:
    std::vector<VariableDeclaration*> var_list;

  public:
    VariableDeclarationList();
    void AddDeclaration(VariableDeclaration* declaration);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~VariableDeclarationList();
    friend class LLVMIRGenerator;
};


#endif  // VariableDelarationList_hpp
