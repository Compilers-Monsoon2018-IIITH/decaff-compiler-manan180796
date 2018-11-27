
#if !defined(FieldList_hpp)
#define FieldList_hpp

#include <AstNode.hpp>
#include <Field.hpp>
#include <vector>

class FieldList : public AstNode {
  private:
    std::vector<Field *> field_list;

  public:
    FieldList(/* args */);
    void AddField(Field *field);
    virtual void accept(Visitor *visitor) { visitor->visit(this); }
    ~FieldList();
    friend class LLVMIRGenerator;
};


#endif  // FieldList_hpp
