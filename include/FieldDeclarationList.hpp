#if !defined(FieldDeclarationList_hpp)
#define FieldDeclarationList_hpp

#include <AstNode.hpp>
#include <FieldDeclaration.hpp>
#include <vector>


class FieldDeclarationList : public AstNode {
  private:
    std::vector<FieldDeclaration*> decl_list;

  public:
    FieldDeclarationList(/* args */);

    void AddDeclaration(FieldDeclaration* decl);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~FieldDeclarationList();
    friend class LLVMIRGenerator;
};


#endif  // FieldDeclarationList_hpp