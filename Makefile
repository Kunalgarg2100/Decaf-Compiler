CC=g++
CFLAGS=-Wall `llvm-config-6.0 --cxxflags --ldflags --system-libs --libs core`

parser: parser.y scanner.l
		bison -d parser.y
		flex scanner.l
		$(CC) $(CFLAGS) -o parser parser.tab.c lex.yy.c -ll

clean:
	rm -f parser parser.tab.c lex.yy.c parser.tab.h
