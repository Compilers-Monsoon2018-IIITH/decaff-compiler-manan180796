%{
    #include <stdio.h>
    #include<iostream>
    #include<Common.hpp>
    extern "C" int yylex();
    extern "C" int yyparse();
    extern "C" FILE *yyin;
    extern "C" int line_num;
    extern union Node yylval;
    extern "C" int errors;
    void yyerror(const char *s);
%}


%token eq minus_eq plus_eq

%token <boolean> bool_literal 
%token <number> decimal_literal 
%token <number> hex_literal 
%token <number> char_literal 
%token <string_lit> string_literal
%token <type> _type_
%token <string_lit> id

// keywords
%token callout _class_ _program_ _void_ _if_ _for_ _return_ _break_ _continue_ _else_

// regular tokens
%token ',' ';'

// operator tokens
// %right '=' add_assign sub_assign
%left or_op
%left and_op
%left eq_op not_eq_op
%left gr_eq_op le_eq_op '<' '>'
%left '+' '-'
%left '*' '/' '%'
%left '!'

// Non-Terminal types
%type <program> PROGRAM;
%type <method_declaration_list> method_declaration_list;
%type <field_declaration_list> field_declaration_list;
%type <field_declaration> field_declaration;
%type <field_list> field_list;
%type <field> field;
%type <method_declaration> method_declaration;
%type <argument_declaration_list> argument_declaration_list;
%type <argument_declaration> argument_declaration;
%type <block> block;
%type <statement_list> statement_list;
%type <variable_declaration_list> variable_declaration_list;
%type <variable_declaration> variable_declaration;
%type <id_list> id_list;
%type <statement> statement;
%type <string_lit> assignment_operator;
%type <expression> expression;
%type <unary_expression> unary_expression;
%type <binary_expression> binary_expression;
%type <string_lit> binary_operation;
%type <string_lit> binary_arithematic_operation;
%type <string_lit> binary_relation_operation;
%type <location> location;
%type <method_call> method_call;
%type <string_lit> method_name;
%type <expression_list> expression_list;
%type <callout_arg_list> callout_arg_list;
%type <callout_arg> callout_arg;
%type <literal> literal;
%type <int_literal> int_literal;


%start PROGRAM

%%

PROGRAM:
        _class_ _program_ '{' field_declaration_list method_declaration_list '}'
            {$$ = new Program($4,$5);}
    |   _class_ _program_ '{' method_declaration_list '}'
            {$$ = new Program(nullptr,$4);}
    |   _class_ _program_ '{' field_declaration_list '}'
            {$$ = new Program($4,nullptr);}
    |   _class_ _program_ '{'  '}'
            {$$ = new Program(nullptr,nullptr);}
;


method_declaration_list:
        method_declaration
            {$$ = new MethodDeclarationList();$$->AddDeclaration($1);}
    |   method_declaration_list method_declaration
            {$$->AddDeclaration($2);}
;


field_declaration_list:
        field_declaration
            {$$=new FieldDeclarationList();$$->AddDeclaration($1);}
    |   field_declaration_list field_declaration 
            {$$->AddDeclaration($2);}
;

field_declaration:
        _type_ field_list ';'
            {$$ = new FieldDeclaration($1,$2);}
;

field_list:
        field
            {$$ = new FieldList();$$->AddField($1);}
    |   field_list ',' field
            {$$->AddField($3);}
;

field:
        id
            {$$ = new Field(*($1));}
    |   id '[' int_literal ']'
            {$$ = new Field(*($1),$3);}
;


method_declaration:
        _void_ id '(' argument_declaration_list ')' block
            {$$ = new MethodDeclaration(Void,*($2),$4,$6);}
    |   _type_ id '(' argument_declaration_list ')' block
            {$$ = new MethodDeclaration($1,*($2),$4,$6);}
    |   _void_ id '('  ')' block
            {$$ = new MethodDeclaration(Void,*($2),new ArgumentDeclarationList(),$5);}
    |   _type_ id '('  ')' block
            {$$ = new MethodDeclaration($1,*($2),new ArgumentDeclarationList(),$5);}
;

argument_declaration_list:
        argument_declaration
            {$$ = new ArgumentDeclarationList();$$->AddArgument($1);}
    |   argument_declaration_list ',' argument_declaration
            {$$->AddArgument($3);}
;

argument_declaration:
        _type_ id
            {$$ = new ArgumentDeclaration($1,*($2));}
;


block:
        '{' variable_declaration_list statement_list '}'
            {$$ = new Block($2,$3);}
    |   '{' variable_declaration_list '}'
            {$$ = new Block($2,new StatementList());}
    |   '{' statement_list '}'
            {$$ = new Block(new VariableDeclarationList(),$2);}
    |   '{' '}'
            {$$ = new Block(new VariableDeclarationList(),new StatementList());}
;


statement_list:
        statement
            {$$ = new StatementList();$$->AddStatement($1);}
    |   statement_list statement
            {$$->AddStatement($2);}
;

variable_declaration_list:
        variable_declaration
            {$$ = new VariableDeclarationList();$$->AddDeclaration($1);}
    |   variable_declaration_list variable_declaration
            {$$->AddDeclaration($2);}
;

variable_declaration:
        _type_ id_list ';'
            {$$ = new VariableDeclaration($1,$2);}
;


id_list:
        id
            {$$ = new IdList();$$->AddId(*($1));}
    |   id_list ',' id
            {$$->AddId(*($3));}
;

statement:
        location assignment_operator expression ';'
            {$$ = new AssignmentStatement($1,*($2),$3);}
    |   method_call ';'
            {$$ = new MethodStatement($1);}
    |   _if_ '(' expression ')' block _else_ block
            {$$ = new IfStatement($3,$5,$7);} 
    |   _if_ '(' expression ')' block
            {$$ = new IfStatement($3,$5,nullptr);} 
    |   _for_ id eq expression ',' expression block
            {$$ = new ForStatement(*($2),$4,$6,$7);}
    |   _return_ expression ';'
            {$$ = new ReturnStatement($2);}
    |   _return_ ';'
            {$$ = new ReturnStatement();}
    |   _continue_ ';'
            {$$ = new ContinueStatement();}
    |   _break_ ';'
            {$$ = new BreakStatement();}
    |   block
            {$$ = $1;}
;


assignment_operator:
        eq
            {$$ = new std::string("=");}
    |   minus_eq
            {$$ = new std::string("-=");}
    |   plus_eq   
            {$$ = new std::string("+=");}
;


expression:
        unary_expression
            {$$ = $1;}
    |   binary_expression
            {$$ = $1;}
;

unary_expression: 
        '(' expression ')'
            {$$ = new NestedUnaryExpression($2);}
    |   '-' expression
            {$$ = new UnaryOperation("-",$2);}
    |   '!' expression
            {$$ = new UnaryOperation("!",$2);}
    |   location
            {$$ = $1;}
    |   method_call
            {$$ = $1;}
    |   literal
            {$$ = $1;}
;



binary_expression:
        expression binary_operation expression
            {$$ = new BinaryExpression($1,*($2),$3);}
;	

binary_operation:
        binary_arithematic_operation
            {$$ = $1;}
    |   binary_relation_operation
            {$$ = $1;}
;

binary_arithematic_operation:
        '+'
            {$$ = new std::string("+");}
    |   '-'
            {$$ = new std::string("-");}
    |   '*'
            {$$ = new std::string("*");}
    |   '/'
            {$$ = new std::string("/");}
    |   '%'
            {$$ = new std::string("%");}
;

binary_relation_operation:
        '<'
            {$$ = new std::string("<");}
    |   '>'
            {$$ = new std::string(">");}
    |   or_op     
            {$$ = new std::string("||");}
    |   and_op     
            {$$ = new std::string("&&");}
    |   eq_op     
            {$$ = new std::string("==");}
    |   not_eq_op     
            {$$ = new std::string("!=");}
    |   le_eq_op     
            {$$ = new std::string("<=");}
    |   gr_eq_op     
            {$$ = new std::string(">=");}
;

location: 
        id
            {$$ = new Location(*($1));}
    | 	id '[' expression ']'
            {$$ = new Location(*($1),$3);}
;

method_call:
        method_name '(' ')'
            {$$ = new SimpleMethod(*($1));}
    |   method_name '(' expression_list ')'
            {$$ = new SimpleMethod(*($1),$3);}
    |   callout '(' string_literal ')'
            {$$ = new CalloutMethod(*($3));}
    |   callout '(' string_literal ',' callout_arg_list ')'
            {$$ = new CalloutMethod(*($3),$5);}
;

method_name:
        id
            {$$ = $1;}
;

expression_list:
        expression
            {$$ = new ExpressionList();$$->AddExpression($1);}
    |   expression_list ',' expression
            {$$->AddExpression($3);}
;
callout_arg_list:
        callout_arg
            {$$ = new CalloutArgList();$$->AddArgument($1);}
    |   callout_arg_list ',' callout_arg    
            {$$->AddArgument($3);}
;

callout_arg:
        string_literal
            {$$ = new CalloutArg(*($1));}
    |   expression
            {$$ = new CalloutArg($1);}
;

literal:
        int_literal
            {$$ = $1;}
    |   char_literal
            {$$ = new CharLiteral($1);}
    |   bool_literal
            {$$ = new BoolLiteral($1);}
;

int_literal:
        decimal_literal
            {$$ = new IntLiteral($1);}
    |   hex_literal
            {$$ = new IntLiteral($1);}
;


%%

int main(int argc, char **argv)
{
    yyparse();
    // printf("Parsing Over\n");
    std::cout<<"Parsing Over\n";
}

int yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}