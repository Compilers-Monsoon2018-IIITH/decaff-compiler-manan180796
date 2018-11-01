digit       [0-9]
alpha       [a-zA-Z_]
hex_digit   [0-9a-fA-F]
char        \\\"|\\'|\\n|\\t|\\\\|[^\\"']


%{
#include "parser.tab.h"
// #define YY_DECL int yylex()
int lineno = 0;
%}

%%
"true"                          {return bool_literal;}
"false"                         {return bool_literal;}

"class"                         {return _class_;}
"Program"                       {return _program_;}
"int"                           {return _type_;}
"boolean"                       {return _type_;}
"void"                          {return _void_;}
"if"                            {return _if_;}
"else"                          {return _else_;}
"for"                           {return _for_;}
"return"                        {return _return_;}
"break"                         {return _break_;}
"continue"                      {return _continue_;}
"callout"                       {return callout;}




{alpha}({alpha}|{digit})*       {return id;}
{digit}+                        {return decimal_literal;}
0x{hex_digit}+                  {return hex_literal;}
'{char}'                        {return char_literal;}
\"{char}*\"                     {return string_literal;}


"<="                            {return le_eq_op;}
">="                            {return gr_eq_op;}

"=="                            {return eq_op;}
"!="                            {return not_eq_op;}

"&&"                            {return and_op;}
"||"                            {return or_op;}


"="                             {return eq;}
"-="                            {return minus_eq;}
"+="                            {return plus_eq;}


"+"                             {return '+';}
"-"                             {return '-';}
"*"                             {return '*';}
"/"                             {return '/';}
"%"                             {return '%';}

"<"                             {return '<';}
">"                             {return '>';}
"!"                             {return '!';}


";"                             {return ';';}
","                             {return ',';}



"("                             {return '(';}
")"                             {return ')';}

"["                             {return '[';}
"]"                             {return ']';}

"{"                             {return '{';}
"}"                             {return '}';}

[ \t]                           { }
\n                              {++lineno;}
.                               { printf("Line No %d: Unrecognized Character\n", lineno); }

%%

