# Decaff Compiler
## Structure

- [scanner.l](./scanner.l) contains code for scanner
- [parser.l](./parser.l) contains code for parser
- [ast.h](./ast.h) contains structure and definations of AST nodes
- [visitor.h](./visitor.h) contains code for AST traversal
- [codegenvistor.h](./codegenvistor.h) contains code for generating IR
- [test-programs](./test-programs) contains some sample Decaf Programs
  - [working-programs](./test-programs/working-programs) contains Decaf Programs for whose AST construction and IR generation are successfully done by code. 
  - [non-working-programs](./test-programs/non-working-programs)  contains Decaf Programs for whose AST construction is done but IR generation is giving errors. 
  - [c-programs](./test-programs/c-programs)  contains C- Programs equivalent to Deacf Program which were used to understand IR generation. 
- [Makefile](./Makefile) for compiling scanner and parser

## Running Code 

```bash
make
```

`./parser` executable will be created along with some other files. To check if the program is syntactically valid 

```bash
./parser < <file_name>
```
These are the different messages given by the code:
- "Program Parsed successfully" : If the input file is successfully parsed and tokenized output of scanner is stored in `flex_output.txt`
- "AST generated" : If AST has been successfully generated and output is stored in `AST_output.txt`
- Then IR generation is started and its output is stored in `IR_output.txt`

To obtain the output of Decaf Program from IR, we need to execute bitcode using `lli`.
```bash
lli IR_output.txt
```

To convert the C program to its IR, command is
```bash
clang-6.0 -cc1 -emit-llvm <filename>.c -o <filename>.ll
```

### Examples to run test-programs

```bash
# This will give the tokenized output for sumn.dcf
./parser < test-programs/working-programs/sumn.dcf
# This will give the tokenized output for bubble.dcf
./parser < test-programs/working-programs/bubble.dcf
# This will give the tokenized output for nextmax.dcf
./parser < test-programs/working-programs/nextmax.dcf
```
 

## Description

### Things implemented
-	Nest If-Else statements
-	Local Methods
-	Multiple Function Calls
-	Callout function for Array
-	Nested For loops
-	Binary Exprs and Assignment Statement
-	Little Support for Recursive Functions

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


This is the output of AST will look like:
```
ForstatementASTnode
<varname = i 
Initial condn
IntLitExprASTnode
<integer value = "1">
Break condn
LocationASTnode
<varname = n 
Block statement
BlockstatementASTnode
VardecllistASTnode
StatementlistASTnode
AssignstatementASTnode
LocationASTnode
<varname = sum 
<operator = = 
BinaryExprASTnode
LocationASTnode
<varname = sum 
LocationASTnode
<varname = i 
binop is +
```
The IR for Loop by code:
```
  %0 = load i32, i32* %n
  store i32 1, i32* %i, align 4
  br label %loop

loop:                                             ; preds = %loop, %entry
  %i1 = phi i32 [ 1, %entry ], [ %nextvar, %loop ]
  %1 = load i32, i32* %sum
  %2 = load i32, i32* %i
  %addop = add i32 %1, %2
  store i32 %addop, i32* %sum, align 4
  %i2 = load i32, i32* %i, align 4
  %nextvar = add i32 %i2, 1
  store i32 %nextvar, i32* %i, align 4
  %loopcondition = icmp slt i32 %nextvar, %0
  br i1 %loopcondition, label %loop, label %afterloop

afterloop:                                        ; preds = %loop
```
IR generated by Clang from c-program is :
```
store i32 0, i32* %i, align 4
br label %1

; <label>:1:                                      ; preds = %7, %0
  %2 = load i32, i32* %i, align 4
  %3 = load i32, i32* %n, align 4
  %cmp = icmp slt i32 %2, %3
  br i1 %cmp, label %4, label %9

; <label>:4:                                      ; preds = %1
  %5 = load i32, i32* %sum, align 4
  %6 = load i32, i32* %i, align 4
  %add = add nsw i32 %5, %6
  store i32 %add, i32* %sum, align 4
  br label %7

; <label>:7:                                      ; preds = %4
  %8 = load i32, i32* %i, align 4
  %inc = add nsw i32 %8, 1
  store i32 %inc, i32* %i, align 4
  br label %1

; <label>:9:                                      ; preds = %1
```

## Further Improvements
I haven't implement codegen for continue, break and return statement. Also, I haven't taken care of scope of variables within methods.