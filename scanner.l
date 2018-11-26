digit       [0-9]
alpha       [a-zA-Z_]
hex_digit   [0-9a-fA-F]
char        \\\"|\\'|\\n|\\t|\\\\|[^\\"']


%{
#include<Common.hpp>
#include<string>
#include "parser.tab.h"
#define YY_DECL extern "C" int yylex()
extern union Node yylval;
int lineno = 0;

void yyerror (char const *s){
    // fl=1;
    fprintf (stderr, "%s at statement -> %d\nNot parsed completely\n", s,yylineno);
}

%}

%%
"true"                          {yylval.boolean=true; return bool_literal;}
"false"                         {yylval.boolean=false;return bool_literal;}

"class"                         {return _class_;}
"Program"                       {return _program_;}
"int"                           {yylval.type = Int;return _type_;}
"boolean"                       {yylval.type = Bool;return _type_;}
"void"                          {return _void_;}
"if"                            {return _if_;}
"else"                          {return _else_;}
"for"                           {return _for_;}
"return"                        {return _return_;}
"break"                         {return _break_;}
"continue"                      {return _continue_;}
"callout"                       {return callout;}




{alpha}({alpha}|{digit})*       {yylval.string_lit = new std::string(yytext);return id;}
{digit}+                        {yylval.number = std::stoi(yytext);return decimal_literal;}
0x{hex_digit}+                  {return hex_literal;}
'{char}'                        {yylval.number = yytext[0];return char_literal;}
\"{char}*\"                     {yylval.string_lit = new std::string(yytext+1);yylval.string_lit->pop_back();return string_literal;}


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

