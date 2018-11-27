
#if !defined(ArgumentDeclaration_hpp)
#define ArgumentDeclaration_hpp

#include <AstNode.hpp>
#include <Utility.hpp>
#include <string>

class ArgumentDeclaration : public AstNode {
  private:
    Types type;
    std::string arg_name;

  public:
    ArgumentDeclaration(Types type, std::string arg_name);
    ~ArgumentDeclaration();
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    friend class LLVMIRGenerator;
};


#endif  // ArgumentDeclaration_hpp
