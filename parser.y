%{
#include <stdio.h>	
%}

// literals
%token bool_literal id decimal_literal hex_literal char_literal string_literal

// keywords
%token callout

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

%start expression

%%
expression:
        unary_expression
    |   binary_expression
;

unary_expression: 
        '(' expression ')'
    | 	'-' expression
    | 	'!' expression
    | 	location
    | 	method_call
    | 	literal
;

binary_expression:
        expression '+' expression
    |   expression '-' expression
    |   expression '*' expression
    |   expression '/' expression
    |   expression '%' expression
    |   expression '<' expression
    |   expression '>' expression
    |   expression or_op expression
    |   expression and_op expression
    |   expression eq_op expression
    |   expression not_eq_op expression
    |   expression le_eq_op expression
    |   expression gr_eq_op expression
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

main(int argc, char **argv)
{
    yyparse();
    printf("Parsing Over\n");
}

yyerror(char *s)
{
    fprintf(stderr, "error: %s\n", s);
}