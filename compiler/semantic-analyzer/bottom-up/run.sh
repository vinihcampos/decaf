yacc -d src/parser.y
mv y.tab.c src/
mkdir -p include
mv y.tab.h include/
flex -o src/lex.yy.c src/lexical.l
mkdir -p bin
g++ -std=c++11 -o bin/parser src/y.tab.c src/lex.yy.c -I include/ -ly
rm src/lex.yy.c src/y.tab.c include/y.tab.h

