#if !defined(FieldDeclaration_hpp)
#define FieldDeclaration_hpp


#include <AstNode.hpp>
#include <FieldList.hpp>
#include <Utility.hpp>
#include <vector>


class FieldDeclaration : public AstNode {
  private:
    Types type;
    FieldList* field_list;

  public:
    FieldDeclaration(Types type, FieldList* field_list);
    ~FieldDeclaration();
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
};


#endif  // FieldDeclaration_hpp