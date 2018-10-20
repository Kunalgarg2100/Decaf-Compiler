CC=g++
CFLAGS=-Wall -std=c++14

parser: parser.y scanner.l
		bison -d parser.y
		flex scanner.l
		$(CC) $(CFLAGS) -o parser parser.tab.c lex.yy.c -ll

clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h
