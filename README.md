# Decaff Compiler
## Structure

- [scanner.l](./scanner.l) contains the code for scanner
- [parser.l](./parser.l) conatins the code for parser
- [test-programs](./test-programs) contains some sample Decaf Programs
- [Makefile](./Makefile) for compiling scanner and parser

## Running Code 

```bash
make
```

`./parser` executable will be created along with some other files. To check if the program is syntactically valid 

```bash
./parser < <file_name>
```
If the input file is successfully parsed then "Program Parsed successfully" message is given to the users else the parser will report some error and try to give appropriate diagnostic information to the user.

### Examples to run test-programs

```bash
# This will give the tokenized output for sumn.dcf
./parser < test-programs/sumn.dcf
# This will give the tokenized output for bubble.dcf
./parser < test-programs/bubble.dcf
# This will give the tokenized output for merge.dcf
./parser < test-programs/merge.dcf
# This will give the tokenized output for quick.dcf
./parser < test-programs/quick.dcf
# This will give the tokenized output for nextmax.dcf
./parser < test-programs/nextmax.dcf
```

## Description

**Scanner :** The scanner’s task is to transform a stream of characters into a stream of words in the input language. It applies a set of rules to determine whether or not each word is legal in the source language. If the word is valid, the scanner classifies it into a syntactic category, or “part of speech.”.<br/> Thus the scanner takes a stream of characters and converts it to a stream of classified words—that is, **pairs of the form (p,s), where p is the word’s part of speech and s is its spelling**.
<br/>Example : ("FOR",*for*), ("INTEGER_LITERAL",*123*), ("STRING",*"hello"*)<br/><br/>
**Parser :** The parser’s task is to determine if the input program, represented by the stream of classified words produced by the scanner, is a valid sentence in the programming language. Parser attempts to build a derivation for the input program, using a grammar for the programming language. The parser derives a **syntactic structure for the program**, fitting the words into a grammatical model of the source programming language. 

Lets take the following program from decaf language :

```pseudocode
for i=1, n {
	sum = sum + i;
}
```

This is the output that scanner will generate :

```
FOR
IDENTIFER:i
EQ:=
INTEGER_LITERAL:1
COMMA:,
IDENTIFER:n
COB:{

IDENTIFER:sum
EQ:=
IDENTIFER:sum
ADD:+
IDENTIFER:i
SEMICOLON:;

CCB:}
```

As we can see that the scanner has assigned tokens to the input  stream of characters.

Now parser will try to derive the syntactic structure for the program, fitting the tokens into a grammatical model of the source programming language. If the input stream is not a valid program, the parser reports the problem and appropriate diagnostic information to the user.