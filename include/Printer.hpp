#if !defined(Printer_hpp)
#define Printer_hpp


#include <Common.hpp>
#include <iostream>
#include <string>


class Printer : public Visitor {
  public:
    // Implemented
    virtual void visit(ArgumentDeclaration* argument_declaration) override {
        std::cout << "argument_declaration" << std::endl;
    }
    virtual void visit(
        ArgumentDeclarationList* argument_declaration_list) override {
        std::cout << "argument_declaration_list" << std::endl;
    }
    virtual void visit(AssignmentStatement* assignment_statement) override {
        std::cout << "assignment_statement" << std::endl;
    }
    virtual void visit(AstNode* ast_node) override {
        std::cout << "ast_node" << std::endl;
    }
    virtual void visit(BinaryExpression* binary_expression) override {
        std::cout << "binary_expression" << std::endl;
    }
    virtual void visit(BoolLiteral* bool_literal) override {
        std::cout << "bool_literal" << std::endl;
    }
    virtual void visit(Block* block) override {
        std::cout << "block" << std::endl;
    }
    virtual void visit(BreakStatement* break_statement) override {
        std::cout << "break_statement" << std::endl;
    }
    virtual void visit(CalloutArg* callout_arg) override {
        std::cout << "callout_arg" << std::endl;
    }
    virtual void visit(CalloutArgList* callout_arg_list) override {
        std::cout << "callout_arg_list" << std::endl;
    }
    virtual void visit(CalloutMethod* callout_method) override {
        std::cout << "callout_method" << std::endl;
    }
    virtual void visit(CharLiteral* char_literal) override {
        std::cout << "char_literal" << std::endl;
    }
    virtual void visit(ContinueStatement* continue_statement) override {
        std::cout << "continue_statement" << std::endl;
    }
    virtual void visit(Expression* expression) override {
        std::cout << "expression" << std::endl;
    }
    virtual void visit(ExpressionList* expression_list) override {
        std::cout << "expression_list" << std::endl;
    }
    virtual void visit(Field* field) override {
        std::cout << "field" << std::endl;
    }
    virtual void visit(FieldDeclaration* field_declaration) override {
        std::cout << "field_declaration" << std::endl;
    }
    virtual void visit(FieldDeclarationList* field_declaration_list) override {
        std::cout << "field_declaration_list" << std::endl;
    }
    virtual void visit(FieldList* field_list) override {
        std::cout << "field_list" << std::endl;
    }
    virtual void visit(ForStatement* for_statement) override {
        std::cout << "for_statement" << std::endl;
    }
    virtual void visit(IdList* id_list) override {
        std::cout << "id_list" << std::endl;
    }
    virtual void visit(IfStatement* if_statement) override {
        std::cout << "if_statement" << std::endl;
    }
    virtual void visit(IntLiteral* int_literal) override {
        std::cout << "int_literal" << std::endl;
    }
    virtual void visit(Literal* literal) override {
        std::cout << "literal" << std::endl;
    }
    virtual void visit(Location* location) override {
        std::cout << "location" << std::endl;
    }
    virtual void visit(MethodCall* method_call) override {
        std::cout << "method_call" << std::endl;
    }
    virtual void visit(MethodDeclaration* method_declaration) override {
        std::cout << "method_declaration" << std::endl;
    }
    virtual void visit(
        MethodDeclarationList* method_declaration_list) override {
        std::cout << "method_declaration_list" << std::endl;
    }
    virtual void visit(MethodStatement* method_statement) override {
        std::cout << "method_statement" << std::endl;
    }
    virtual void visit(
        NestedUnaryExpression* nested_unary_expression) override {
        std::cout << "nested_unary_expression" << std::endl;
    }
    virtual void visit(ReturnStatement* return_statement) override {
        std::cout << "return_statement" << std::endl;
    }
    virtual void visit(SimpleMethod* simple_method) override {
        std::cout << "simple_method" << std::endl;
    }
    virtual void visit(Statement* statement) override {
        std::cout << "statement" << std::endl;
    }
    virtual void visit(StatementList* statement_list) override {
        std::cout << "statement_list" << std::endl;
    }
    virtual void visit(UnaryExpression* unary_expression) override {
        std::cout << "unary_expression" << std::endl;
    }
    virtual void visit(UnaryOperation* unary_operation) override {
        std::cout << "unary_operation" << std::endl;
    }
    virtual void visit(VariableDeclaration* variablle_declaration) override {
        std::cout << "variablle_declaration" << std::endl;
    }
    virtual void visit(
        VariableDeclarationList* variable_declaration_list) override {
        std::cout << "variable_declaration_list" << std::endl;
    }
    static Printer* printer;
};

Printer* Printer::printer = new Printer();

#endif  // Printer_hpp