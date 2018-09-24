flex -o src/lex.yy.c src/lexical.lex
mkdir -p bin
g++ -std=gnu++0x -o bin/iterative src/iterative.cpp src/lex.yy.c -I include/
rm src/lex.yy.c
