// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
//
// This program only needs to handle arguments that satisfy
// R0 >= 0, R1 >= 0, and R0*R1 < 32768.

// Put your code here.

//@R0
//D=M
//@num1
//M=D 

//@R1 
//D=M 
//@num2
//M=D 

@i 
M=1 

@R2
M=0 

(LOOP)
@R1
D=M 
@i 
D=D-M //D = num2-i
@END 
D;JLT //JUMP TO END ID i>num2 I.E. num2-I<0

@R2 
D=M 
@R0 
D=D+M 
@R2 
M=D   //prod = prod + num2
@i 
M=M+1 //i++
@LOOP 
0;JMP    

(END)
@END
0;JMP