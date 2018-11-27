#if !defined(Visitor_hpp)
#define Visitor_hpp

class Visitor {
  public:
    virtual void visit(class ArgumentDeclaration* argument_declaration) {}
    virtual void visit(
        class ArgumentDeclarationList* argument_declaration_list) {}
    virtual void visit(class AssignmentStatement* assignment_statement) {}
    virtual void visit(class AstNode* ast_node) {}
    virtual void visit(class BinaryExpression* binary_expression) {}
    virtual void visit(class Block* block) {}
    virtual void visit(class BoolLiteral* bool_literal) {}
    virtual void visit(class BreakStatement* break_statement) {}
    virtual void visit(class CalloutArg* callout_arg) {}
    virtual void visit(class CalloutArgList* callout_arg_list) {}
    virtual void visit(class CalloutMethod* callout_method) {}
    virtual void visit(class CharLiteral* char_literal) {}
    virtual void visit(class ContinueStatement* continue_statement) {}
    virtual void visit(class Expression* expression) {}
    virtual void visit(class ExpressionList* expression_list) {}
    virtual void visit(class Field* field) {}
    virtual void visit(class FieldDeclaration* field_declaration) {}
    virtual void visit(class FieldDeclarationList* field_declaration_list) {}
    virtual void visit(class FieldList* field_list) {}
    virtual void visit(class ForStatement* for_statement) {}
    virtual void visit(class IdList* id_list) {}
    virtual void visit(class IfStatement* if_statement) {}
    virtual void visit(class IntLiteral* int_literal) {}
    virtual void visit(class Literal* literal) {}
    virtual void visit(class Location* location) {}
    virtual void visit(class MethodCall* method_call) {}
    virtual void visit(class MethodDeclaration* method_declaration) {}
    virtual void visit(class MethodDeclarationList* method_declaration_list) {}
    virtual void visit(class MethodStatement* method_statement) {}
    virtual void visit(class NestedUnaryExpression* nested_unary_expression) {}
    virtual void visit(class Program* program) {}
    virtual void visit(class ReturnStatement* return_statement) {}
    virtual void visit(class SimpleMethod* simple_method) {}
    virtual void visit(class Statement* statement) {}
    virtual void visit(class UnaryExpression* unary_expression) {}
    virtual void visit(class UnaryOperation* unary_operation) {}
    virtual void visit(class VariableDeclaration* variablle_declaration) {}
    virtual void visit(
        class VariableDeclarationList* varialble_declaration_list) {}
};


#endif  // Visitor_hpp
