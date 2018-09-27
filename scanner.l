digit       [0-9]
alpha       [a-zA-Z_]
hex_digit   [0-9a-fA-F]
char        \\\"|\\'|\\n|\\t|\\\\|[^\\"']


%{
#include "parser.tab.h"
int lineno = 0;
%}

%%
"true"                          {return bool_literal;}
"false"                         {return bool_literal;}
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

