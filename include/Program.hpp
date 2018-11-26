#if !defined(Program_hpp)
#define Program_hpp

#include <AstNode.hpp>
#include <FieldDeclarationList.hpp>
#include <MethodDeclarationList.hpp>


class Program : public AstNode {
  private:
    FieldDeclarationList* field_list;
    MethodDeclarationList* method_list;

  public:
    Program(FieldDeclarationList* field_list,
            MethodDeclarationList* method_list);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~Program();
};


#endif  // Program_hpp