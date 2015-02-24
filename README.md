# VIC_ASM_Emulator
This is an attempt to create an emulator for a hypothetical 16 bit microprocessor. The microprocessor supports arithmetic, logical, conditional and unconditional jump instructions (Forward reference has not been implemented). 



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
#      		Instructions	    #
#####################################	

1. Write your program in "ASMCODE.vic" file by referring to the opcodes in the readme.md above.
2. Execute "asmcode.exe" or compile "asmcode.c"
3. A number of output files are generated if successful assembly was done.
4. Execute "binrun.exe" or compile "binrun.c", (It uses binary.txt generated earlier in step 3 as source input).
5. The register values in the end at the end of program values are shown along with last set flags.
