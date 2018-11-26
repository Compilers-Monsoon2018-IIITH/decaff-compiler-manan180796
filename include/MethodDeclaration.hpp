
#if !defined(MethodDeclaration_hpp)
#define MethodDeclaration_hpp


#include <ArgumentDeclarationList.hpp>
#include <AstNode.hpp>
#include <Block.hpp>
#include <Utility.hpp>
#include <string>

class MethodDeclaration : public AstNode {
  private:
    Types return_type;
    std::string name;
    ArgumentDeclarationList* arg_list;
    Block* body;

  public:
    MethodDeclaration(Types retutn_type, std::string name,
                      ArgumentDeclarationList* arg_list, Block* body);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~MethodDeclaration();
};


#endif  // MethodDeclaration_hpp
