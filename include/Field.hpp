
#if !defined(Field_hpp)
#define Field_hpp

#include <AstNode.hpp>
#include <IntLiteral.hpp>
#include <string>

class Field : public AstNode {
  private:
    std::string name;
    IntLiteral* size;

  public:
    Field(std::string name, IntLiteral* size = nullptr);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~Field();
    friend class LLVMIRGenerator;
};


#endif  // Field_hpp
