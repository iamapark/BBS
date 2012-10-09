cp ../data/board.index board.index
rm mkbbs
gcc -o mkbbs mkbbs.c
./mkbbs
