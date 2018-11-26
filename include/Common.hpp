#if !defined(Common_hpp)
#define Common_hpp

#include <ArgumentDeclaration.hpp>
#include <ArgumentDeclarationList.hpp>
#include <AssignmentStatement.hpp>
#include <AstNode.hpp>
#include <BinaryExpression.hpp>
#include <Block.hpp>
#include <BoolLiteral.hpp>
#include <BreakStatement.hpp>
#include <CalloutArg.hpp>
#include <CalloutMethod.hpp>
#include <CharLiteral.hpp>
#include <ContinueStatement.hpp>
#include <Expression.hpp>
#include <ExpressionList.hpp>
#include <Field.hpp>
#include <FieldDeclaration.hpp>
#include <FieldDeclarationList.hpp>
#include <FieldList.hpp>
#include <ForStatement.hpp>
#include <IdList.hpp>
#include <IfStatement.hpp>
#include <IntLiteral.hpp>
#include <Literal.hpp>
#include <Location.hpp>
#include <MethodCall.hpp>
#include <MethodDeclaration.hpp>
#include <MethodDeclarationList.hpp>
#include <MethodStatement.hpp>
#include <NestedUnaryExpression.hpp>
#include <Program.hpp>
#include <ReturnStatement.hpp>
#include <SimpleMethod.hpp>
#include <Statement.hpp>
#include <StatementList.hpp>
#include <UnaryExpression.hpp>
#include <UnaryOperation.hpp>
#include <VariableDeclaration.hpp>
#include <VariableDeclarationList.hpp>
#include <string>


union Node {
    int number;
    Types type;
    bool boolean;
    std::string* string_lit;
    class Program* program;
    class MethodDeclarationList* method_declaration_list;
    class FieldDeclarationList* field_declaration_list;
    class FieldDeclaration* field_declaration;
    class FieldList* field_list;
    class Field* field;
    class MethodDeclaration* method_declaration;
    class ArgumentDeclarationList* argument_declaration_list;
    class ArgumentDeclaration* argument_declaration;
    class Block* block;
    class StatementList* statement_list;
    class VariableDeclarationList* variable_declaration_list;
    class VariableDeclaration* variable_declaration;
    class IdList* id_list;
    class Statement* statement;
    class Expression* expression;
    class UnaryExpression* unary_expression;
    class BinaryExpression* binary_expression;
    class Location* location;
    class MethodCall* method_call;
    class ExpressionList* expression_list;
    class CalloutArgList* callout_arg_list;
    class CalloutArg* callout_arg;
    class Literal* literal;
    class IntLiteral* int_literal;
    Node() {
        number = 0;
        boolean = false;
        string_lit = nullptr;
        program = nullptr;
        method_declaration_list = nullptr;
        field_declaration_list = nullptr;
        field_declaration = nullptr;
        field_list = nullptr;
        field = nullptr;
        method_declaration = nullptr;
        argument_declaration_list = nullptr;
        argument_declaration = nullptr;
        block = nullptr;
        statement_list = nullptr;
        variable_declaration_list = nullptr;
        variable_declaration = nullptr;
        id_list = nullptr;
        statement = nullptr;
        expression = nullptr;
        unary_expression = nullptr;
        binary_expression = nullptr;
        location = nullptr;
        method_call = nullptr;
        expression_list = nullptr;
        callout_arg_list = nullptr;
        callout_arg = nullptr;
        literal = nullptr;
        int_literal = nullptr;
    }
    ~Node() {}
};
typedef union Node YYSTYPE;
#define YYSTYPE_IS_DECLARED 1
#endif  // Common_hpp