// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)

// Pseudo
//n=R0
//m=R1
//i=1
//prod=0
//LOOP:
//if i > m END
//prod=prod+n
//i=i+1
//goto LOOP
//END:
//R2=prod



@R0
D=M
@n
M=D	//n=R0
@END
D; JLE	// if R0 <= 0 

@R1
D=M
@m
M=D	//m=R1
@END
D; JLE  // if R1 <= 0 

@i	
M=1	//i=1

@prod
M=0	//prod=0


(LOOP)
@i
D=M
@m
D=D-M
@END
D; JGT  //if i > m goto END

@prod
D=M
@n
D=D+M
@prod
M=D		//prod = prod + n

@i
M=M+1	//i=i+1
@LOOP
0; JMP

(END)
@prod
D=M
@R2
M=D		//R2= prod
@STOP
0; JMP

(STOP)
@STOP	// stop the program
0;JMP