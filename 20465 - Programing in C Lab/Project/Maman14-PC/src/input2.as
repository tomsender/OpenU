	.entry LOOP
MAIN: inc K
	mov M1[r3][r3],W
	.extern W
	add r2,STR
LOOP: jmp W
	prn #-5
STR: .string "ab"
	sub r1,r4
	stop
	.entry STR
K: .data 2,7
M1: .mat [2][2] 1,2,3,4


