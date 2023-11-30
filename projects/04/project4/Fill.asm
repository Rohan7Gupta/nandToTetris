// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/04/Fill.asm

// Runs an infinite loop that listens to the keyboard input.
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel;
// the screen should remain fully black as long as the key is pressed. 
// When no key is pressed, the program clears the screen, i.e. writes
// "white" in every pixel;
// the screen should remain fully clear as long as no key is pressed.

// Put your code here.

@8192
D=A 
@R0
M=D //R0=8192  FINAL COUNT/NO OF PIXELS ON SCREEN


@SCREEN
D=A 
@R2 
M=D //STORING SCREEN LOCATION IN R2

//KEYBOARD 
(LOOP)
@R1
M=0
@KBD
D=M
@LOOP2 
D;JNE //JUMP TO LOOP2 IF KEYBOARD ENTRY NOT NULL/0
@LOOP3 
D;JEQ

(LOOP2)
@R0
D=M
@R1
D=D-M
@LOOP
D;JEQ
@R1
D=M 
M=M+1
@R2 
A=D+M 
M=-1
@LOOP2 
0;JMP

(LOOP3)
@R0
D=M
@R1
D=D-M
@LOOP
D;JEQ
@R1
D=M 
M=M+1
@R2 
D=D+M 
A=D 
M=0
@LOOP3 
0;JMP
