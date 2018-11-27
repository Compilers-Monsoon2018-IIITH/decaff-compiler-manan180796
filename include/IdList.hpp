
#if !defined(IdList_hpp)
#define IdList_hpp

#include <AstNode.hpp>
#include <string>
#include <vector>

class IdList {
  private:
    std::vector<std::string> id_list;

  public:
    IdList();
    void AddId(std::string id);
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    ~IdList();
    friend class LLVMIRGenerator;
};


#endif  // IdList_hpp
