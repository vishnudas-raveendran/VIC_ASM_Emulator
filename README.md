# VIC_ASM_Emulator
This is an attempt to create an emulator for a hypothetical 16 bit microprocessor. The microprocessor supports arithmetic, logical, conditional and unconditional jump instructions (Forward reference has not been implemented). 

Use the following opcodes to write programs
|OPCODE	|   MACHINE CODE  |    No.of operands 	| Description					|Syntax					|Remarks							
|add	|	0100000	  	  |		3    			| Addition operation 			|add dest,src1,src2		|dest=src1+src2
|sub	|	0100001	  	  |		3    			| Subtraction operation 		|sub dest,src1,src2		|dest=src2-src1
|mul	|	0100010	  	  |		3    			| Multiplication operation 		|mul dest,src1,src2		|dest=src1*src2
|div	|	0100011	  	  |		3    			| Division operation 			|div dest,src1,src2		|dest=src2/src1
|mov	|	0100100	  	  |		2    			| Move operation 				|mov dest,src			|dest=src
|mod	|	0100101	  	  |		3    			| Modulus operation				|mod dest,src1,src2		|dest=src2%src1
|comp	|	0100110	  	  |		2    			| Comparison operation			|comp src1,src2			|flags are set
|mvi	|	0100111	  	  |		2    			| Move immediate operation		|mvi dest,int_num		|dest=int_num
|jmp	|	0101000	  	  |		1    			| Unconditional jump			|jmp label				|jumps to #label
|jmg	|	0101001	  	  |		1    			| Jump if greater				|jmg label				|jumps if flag bit is set as greater than after a comp operation
|jge	|	0101010	  	  |		1    			| jump if greater than or equal |jge label				|jumps if flag bit is set as greater than or equal to after a comp operation
|jml	|	0101011	  	  |		1    			| jump if less 	     			|jml label				|jumps if flag bit is set as less than after a comp operation   			
|jle	|	0101100	  	  |		1       		| jump if less than or equal 	|jle label				|jumps if flag bit is set as less than or equal after a comp operation
|#label | At run time	  | 	Nil				| Label instruction				|#big					|Instructions execute from next line after label



#####################################
#      Flag Structures 			    #
#####################################


    flag[0] --|
			  |- indicates the status of compare flags:-			  
    flag[1] --|

	flag[2] - indicates any error

--------------------------------------	
	Status of compare flags	
--------------------------------------
 flag[0]  flag[1]					
	1		1		equal 		
	1		0		src1>src2
	0		1   	src1<src2 
	0		0		invalid
-------------------------------------	


#####################################
#      Instruction formats:		    #
#####################################

**
-------------------------------
	Arithemtic operations
-------------------------------
   add, sub, mul, div, mod    
-------------------------------   
opcode	Regd	Regs1	Regs2
7 bits	3 bits	3 bits	3 bits
--------------------------------
**


**
------------------------------
	immediate operations
-------------------------------
   mvi    
------------------------------- 
Opcode	Regd	Immediate value
7 bits	3 bits	6 bits
-------------------------------
**


**
------------------------------
	Jump operations
-------------------------------
   jmp, jml, jle, jmg, jge   
------------------------------- 
Opcode	Label code
7 bits	9 bits
-------------------------------
**


**
------------------------------
	Label instruction
-------------------------------
   #label 
------------------------------- 
Label code
9 bits
-------------------------------
**


#####################################
#      		Note					#
#####################################


1. The source file for the "asmcode.exe" is "ASMCODE.vic". Please use the exact filename for execution.
2. Forward reference has not been implemented.
3. The message "Assembly completed successfully" is shown in the end of executing "asmcode.exe". If you do not see the message it means:
    3.1 There is an assembly programming fault in your ASMCODE.vic program. 
	3.2 A runtime error has occurred 
	3.3 The emulator is not designed to run that ASMCODE.vic code.
4. Please keep "ASMCODE.vic" file where "asmcode.exe" can access. Preferably, on the same directory as "asmcode.exe".
5. Please keep the "binary.txt" file which is auto-generated intermediate file from asmcode.exe in the same directory has "binrun.exe".

#####################################
#      		Instructions			#
#####################################	

1. Write your program in "ASMCODE.vic" file by referring to the opcodes in the readme.md above.
2. Execute "asmcode.exe" or compile "asmcode.c"
3. A number of output files are generated if successful assembly was done.
4. Execute "binrun.exe" or compile "binrun.c", (It uses binary.txt generated earlier in step 3 as source input).
5. The register values in the end at the end of program values are shown along with last set flags.
