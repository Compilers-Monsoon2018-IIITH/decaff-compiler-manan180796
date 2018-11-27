
Include=-Iinclude
flex_flags=-lfl

header_dir=include
source_dir=src
object_dir=obj

parser: parser.tab.c parser.tab.h lex.yy.c  
		g++ -o parser parser.tab.c lex.yy.c obj/*.o ${Include} ${flex_flags}

parser.tab.c: parser.y
	bison -d parser.y

lex.yy.c: scanner.l
	flex scanner.l


clean: 
	rm  parser parser.tab.c parser.tab.h lex.yy.c

all_clean:
	rm -rf parser parser.tab.c parser.tab.h lex.yy.c obj/

obj:
	mkdir obj
