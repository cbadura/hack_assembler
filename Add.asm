// Computes R0 = 2 + 3 (R0 refers to RAM[0])

(START)
@2
D=A
(LOOP)
@3
D=D+A
@0
M=D
@x
D=A
