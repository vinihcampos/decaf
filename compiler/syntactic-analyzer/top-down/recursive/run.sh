flex -o src/lex.yy.c src/lexical.lex
mkdir -p bin
g++ -std=c++11 -o bin/recursive src/recursive.cpp src/lex.yy.c -I include/
rm src/lex.yy.c
