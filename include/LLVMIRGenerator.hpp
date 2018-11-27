#if !defined(LLVMIRGenerator_hpp)
#define LLVMIRGenerator_hpp

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/LegacyPassManager.h>
#include <Common.hpp>
#include <map>
#include <set>
#include <stack>
#include <string>

using namespace llvm;


class LLVMIRGenerator : public Visitor {
  private:
    class Loop {
      public:
        BasicBlock *after_basic_block, *check_basic_block;
        llvm::Value* condition;
        std::string loop_variable;
        PHINode* phi_variable;

        Loop(BasicBlock* afterBlock, BasicBlock* checkBlock, Value* cond,
             std::string var, PHINode* phiVar)
            : after_basic_block(afterBlock),
              check_basic_block(checkBlock),
              condition(cond),
              loop_variable(var),
              phi_variable(phiVar) {}
    };
    Value* return_value;
    Function* return_function;
    LLVMContext context;
    IRBuilder<> builder;
    Module* module;
    std::map<std::string, std::stack<AllocaInst*>> named_values;

    std::stack<Loop*> loop_stack;
    std::stack<std::set<std::string>> name_stack;

  public:
    LLVMIRGenerator();
    ~LLVMIRGenerator();
    AllocaInst* CreateEntryBlockAlloca(Function* TheFunction,
                                       std::string VarName, std::string type);

    void LogError(std::string error_message);

    virtual void visit(Program* program) override;


    // Implemented
    virtual void visit(ArgumentDeclaration* argument_declaration) override;
    virtual void visit(
        ArgumentDeclarationList* argument_declaration_list) override;
    virtual void visit(AssignmentStatement* assignment_statement) override;
    virtual void visit(AstNode* ast_node) override;
    virtual void visit(BinaryExpression* binary_expression) override;
    virtual void visit(BoolLiteral* bool_literal) override;
    virtual void visit(Block* block) override;
    virtual void visit(BreakStatement* break_statement) override;
    virtual void visit(CalloutArg* callout_arg) override;
    virtual void visit(CalloutArgList* callout_arg_list) override;
    virtual void visit(CalloutMethod* callout_method) override;
    virtual void visit(CharLiteral* char_literal) override;
    virtual void visit(ContinueStatement* continue_statement) override;
    virtual void visit(Expression* expression) override;
    virtual void visit(ExpressionList* expression_list) override;
    virtual void visit(Field* field) override;
    virtual void visit(FieldDeclaration* field_declaration) override;
    virtual void visit(FieldDeclarationList* field_declaration_list) override;
    virtual void visit(FieldList* field_list) override;
    virtual void visit(ForStatement* for_statement) override;
    virtual void visit(IdList* id_list) override;
    virtual void visit(IfStatement* if_statement) override;
    virtual void visit(IntLiteral* int_literal) override;
    virtual void visit(Literal* literal) override;
    virtual void visit(Location* location) override;
    virtual void visit(MethodCall* method_call) override;
    virtual void visit(MethodDeclaration* method_declaration) override;
    virtual void visit(MethodDeclarationList* method_declaration_list) override;
    virtual void visit(MethodStatement* method_statement) override;
    virtual void visit(NestedUnaryExpression* nested_unary_expression) override;
    virtual void visit(ReturnStatement* return_statement) override;
    virtual void visit(SimpleMethod* simple_method) override;
    virtual void visit(Statement* statement) override;
    virtual void visit(UnaryExpression* unary_expression) override;
    virtual void visit(UnaryOperation* unary_operation) override;
    virtual void visit(VariableDeclaration* variablle_declaration) override;
    virtual void visit(
        VariableDeclarationList* variable_declaration_list) override;
};


#endif  // LLVMIRGenerator_hpp