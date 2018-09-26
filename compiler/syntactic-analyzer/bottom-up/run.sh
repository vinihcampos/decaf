yacc -d src/parser.y
mv y.tab.c src/
mv y.tab.h include/
lex -o src/lex.yy.c src/lexical.l
cc -o bin/parser src/y.tab.c src/lex.yy.c -I include/ -ly -ll
rm src/lex.yy.c src/y.tab.c include/y.tab.h

