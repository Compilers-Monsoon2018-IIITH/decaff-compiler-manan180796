%{
#include <stdio.h>	
// extern int yylex();
int yyerror(char *s);
%}

// literals
%token bool_literal decimal_literal hex_literal char_literal string_literal

%token eq minus_eq plus_eq

// keywords
%token callout _class_ _program_ _type_ _void_ _if_ _for_ _return_ _break_ _continue_ _else_

// regular tokens
%token id ',' ';'

// operator tokens
// %right '=' add_assign sub_assign
%left or_op
%left and_op
%left eq_op not_eq_op
%left gr_eq_op le_eq_op '<' '>'
%left '+' '-'
%left '*' '/' '%'
%left '!'

%start PROGRAM

%%

PROGRAM:
        _class_ _program_ '{' field_declaration_list method_declaration_list '}'
    |   _class_ _program_ '{' method_declaration_list '}'
    |   _class_ _program_ '{' field_declaration_list '}'
    |   _class_ _program_ '{'  '}'
;


method_declaration_list:
        method_declaration
    |   method_declaration_list method_declaration
;


field_declaration_list:
        field_declaration
    |   field_declaration_list field_declaration 
;

field_declaration:
        _type_ field_list ';'
;

field_list:
        field
    |   field_list ',' field
;

field:
        id
    |   id '[' int_literal ']'
;


method_declaration:
        _void_ id '(' singleton_declaration_list ')' block
    |   _type_ id '(' singleton_declaration_list ')' block
    |   _void_ id '('  ')' block
    |   _type_ id '('  ')' block
;

singleton_declaration_list:
        singleton_declaration
    |   singleton_declaration_list ',' singleton_declaration
;

singleton_declaration:
        _type_ id
;


block:
        '{' variable_declaration_list statement_list '}'
    |   '{' variable_declaration_list '}'
    |   '{' statement_list '}'
    |   '{' '}'
;


statement_list:
        statement
    |   statement_list statement
;

variable_declaration_list:
        variable_declaration
    |   variable_declaration_list variable_declaration
;

variable_declaration:
        _type_ id_list ';'
;


id_list:
        id
    |   id_list ',' id
;

statement:
        location assignment_operator expression ';'
    |   method_call ';'
    |   _if_ '(' expression ')' block _else_ block 
    |   _if_ '(' expression ')' block
    |   _for_ id eq expression ',' expression block
    |   _return_ expression ';'
    |   _return_ ';'
    |   _continue_ ';'
    |   _break_ ';'
    |   block
;


assignment_operator:
        eq
    |   minus_eq
    |   plus_eq   
;


expression:
        unary_expression
    |   binary_expression
;

unary_expression: 
        '(' expression ')'
    |   '-' expression
    |   '!' expression
    |   location
    |   method_call
    |   literal
;



binary_expression:
        expression binary_operation expression
;	

binary_operation:
        binary_arithematic_operation
    |   binary_relation_operation
;

binary_arithematic_operation:
        '+'
    |   '-'
    |   '*'
    |   '/'
    |   '%'
;

binary_relation_operation:
        '<'
    |   '>'
    |   or_op     
    |   and_op     
    |   eq_op     
    |   not_eq_op     
    |   le_eq_op     
    |   gr_eq_op     
;

location: 
        id
    | 	id '[' expression ']'
;

method_call:
        method_name '(' ')'
    |   method_name '(' expression_list ')'
    |   callout '(' string_literal ')'
    |   callout '(' string_literal ',' callout_arg_list ')'
;

method_name:
        id
;

expression_list:
        expression
    |   expression ',' expression_list
;
callout_arg_list:
        callout_arg
    |   callout_arg ',' callout_arg_list    
;

callout_arg:
        string_literal
    |   expression
;

literal:
        int_literal
    |   char_literal
    |   bool_literal
;

int_literal:
        decimal_literal
    |   hex_literal
;


%%

int main(int argc, char **argv)
{
    yyparse();
    printf("Parsing Over\n");
}

int yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}