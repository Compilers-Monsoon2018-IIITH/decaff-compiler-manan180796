
#if !defined(MethodDeclarationList_hpp)
#define MethodDeclarationList_hpp

#include <AstNode.hpp>
#include <MethodDeclaration.hpp>
#include <vector>

class MethodDeclarationList : public AstNode {
  private:
    std::vector<MethodDeclaration*> decl_list;

  public:
    MethodDeclarationList();
    void AddDeclaration(MethodDeclaration* decl);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~MethodDeclarationList();
};


#endif  // MethodDeclarationList_hpp
