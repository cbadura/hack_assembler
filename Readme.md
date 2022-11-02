### OVERVIEW
Assembler for the nand2tetris assembly language (project 6 of the nand2tetris course; see https://www.nand2tetris.org and
N. Nisan, S. Schocken: The Elements of Computing Systems: Building a Modern Computer from First Principles. Cambridge, MA/London 2021 (2nd ed.)).

Hack assembly language specification:
Binary Hack program: A binary Hack program is a sequence of text lines, each consisting of sixteen 0 and 1 characters. If the line starts with a 0, it
represents a binary A-instruction. Otherwise, it represents a binary C-instruction (for these terms, see below).
Assembly Hack program: An assembly Hack program is a sequence of text lines, each being an assembly instruction, a label declaration, or a
comment:
- Assembly instruction: A symbolic A-instruction or a symbolic Cinstruction
- Label declaration: A line of the form (xxx), where xxx is a symbol.
- Symbols (variables and control flow labels) that the user creates are also translated. They are kept in a symbolic table (here a linked list,
see symtable.c and symtable.h
- Memory for all assigned variables is managed by the assembler as well.
- Comment: A line beginning with two slashes (//) is considered a comment and is ignored. In-line comments are also ignored.

### SPECIFICATION
A- (related to memory/register addresses) and C-statements (related to what is computed in the ALU)
are translated.

Translating A-instructions (where value is either non-negative decimal constant or symbol referring to one)
op code of A-instr. is 0, so an instruction such as "@value" (=value in dec) in binary reads: "0valueinbinary"
--> decimal to 15-bit binary conversion is done in bin_conversion.c.

Translating C-instructions is done according to a table of possible instructions: 
<img width="923" alt="Hack instruction set" src="https://user-images.githubusercontent.com/93912698/199454924-5314d2c2-b7c9-43d4-8a34-22054a8f0222.png">

The data structure for this is set up in bin_conversion.h.

Translating label symbols, "(xxx)" (to label destinations of GOTO commands): replace with line number
which is retrieved from a table.
(Label declaration instructions such as "(LOOP)", "(STOP", etc. are not translated but skipped – they
have no instruction line number.)

Variable symbols: they are assigned a mem address starting at 16 (after 16 registers).
All these are kept in the symbolic table; predefined are the following:

symbol  value
R0      0
R1      1
R2      2
...
R15     15
SCREEN  16384
KBD     24576
SP      0
LCL     1
ARG     2
THIS    3
THAT    4


### IMPLEMENTENTATION DETAILS
1) On a first pass, the input file is read for looping symbols (lines that start with opening brackets) which are saved in the symbolic table
(which has been set up with predefined values).

2) On second pass, n is set to 16 (register 17 in the RAM), var symbols are extracted (all the symbols that don't appear in symbol table at this point are vars)
At the same time, all lines of the .asm file are parsed into instruction set entities (in parser.c) and stored in an array of structs (see main.h).

3) In code.c, address instructions are simply converted to binary; the binary codes for control and jump instructions are retrieved; all 16 bit-lines are stored
in a string array.

4) These binary lines are written to an output .hack file.


