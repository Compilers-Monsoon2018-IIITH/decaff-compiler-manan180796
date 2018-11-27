
#if !defined(VariableDeclaration_hpp)
#define VariableDeclaration_hpp

#include <AstNode.hpp>
#include <IdList.hpp>
#include <Utility.hpp>
#include <string>

class VariableDeclaration {
  private:
    Types type;
    IdList* id_list;
    /* data */
  public:
    VariableDeclaration(Types type, IdList* id_list);
    ~VariableDeclaration();
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    friend class LLVMIRGenerator;
};


#endif  // VariableDeclaration_hpp
