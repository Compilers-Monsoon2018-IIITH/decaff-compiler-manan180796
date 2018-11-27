#if !defined(CalloutArgList_hpp)
#define CalloutArgList_hpp


#include <AstNode.hpp>
#include <CalloutArg.hpp>
#include <vector>

class CalloutArgList : public AstNode {
    std::vector<CalloutArg*> argument_list;

  public:
    CalloutArgList();
    virtual void accept(Visitor* visitor) { visitor->visit(this); }
    void AddArgument(CalloutArg* argument);
    friend class LLVMIRGenerator;
};


#endif  // CalloutArgList_hpp