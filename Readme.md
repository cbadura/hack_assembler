###
Assembler for the nand2tetris assembly language (week 6's project; see https://www.nand2tetris.org).
###
Translates (with string processing) an assembly language text file into binary machine language:
A- (related to memory/register addresses) and C-statements (related to what is computed in the ALU)
are translated.
Symbols (variables and control flow labels) that the user creates are also translated.
The program assumes that symbols are already translated (to decimal numbers).
Memory for all assigned variables is managed by the assembler as well.
All white spaces and comments are ignored.

Translating A-instructions (where value is either non-negative decimal constant or symbol referring to one)
op code of A-instr. is 0, so an instruction such as "@value" (=value in dec) in binary reads: "0valueinbinary"
--> decimal to 15-bit binary conversion is needed

Translating C-instructions is done according to a table of possible instructions
symbolic syntax: dest = comp ; jump
op code is 1, then two 1's by convention; then a-bit which is necessary for orientation in command table;
then six bits for comp instr., three bits each for dest and jmp
binary syntax: 111accccccdddjjj

Translating label symbols, "(xxx)" (to label destinations of GOTO commands): replace with line number
which is retrieved from a table.
(Label declaration instructions such as "(LOOP)", "(STOP", etc. are not translated but skipped – they
have no instruction line number.)

Variable symbols: they are assigned a mem address starting at 16 (after 16 registers).

All these are kept in a symbol table; predefined are the following:

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


1) initialize table with these values

 

// 2) read input file
// look for lines that start with opening bracket; while doing this count the lines containing instructions
// first pass: add the label symbols to value table
// second pass: set n to 16,
// extract var symbols (all the symbols that don't appear in symbol table at this point are vars);
// but if value is found, use it to complete instruction

// 3) If instruction is C-instruction, translate

// 4) write binary lines to output file


/* The LEXER just turns the meaningless string into a flat list of things like "number literal",
"string literal", "identifier", or "operator", and can do things like recognizing reserved identifiers
("keywords") and discarding whitespace. Formally, a lexer recognizes some set of Regular languages
A "regular" language is one that can be parsed without any extra state in a single non-backtracking pass. */

The PARSER has the much harder job of turning the stream of "tokens" produced by the lexer into a parse tree
representing the structure of the parsed language.

// parser (chops symbolic code into three fields, then converts to binary)


