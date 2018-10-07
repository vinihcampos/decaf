yacc -d src/parser.y
mv y.tab.c src/
mkdir -p include
mv y.tab.h include/
lex -o src/lex.yy.c src/lexical.l
mkdir -p bin
cc -o bin/parser src/y.tab.c src/lex.yy.c -I include/ -ly
rm src/lex.yy.c src/y.tab.c include/y.tab.h

