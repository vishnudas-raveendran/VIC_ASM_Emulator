// Binary run ver 2
/*****
when you have eliminated the impossible, whatever remains, however improbable, must be the truth
- sherlock holmes
***/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
int debug=1;
char mcode[8],regd[4],regs2[4],regs1[4];int immval=0;
struct dyntabds
 {
 	char label[50];
 	char bin[9];
 	long int pos;
 }dyntabds[10],dynorg[10];
int flag[8];
/*1
   Flag structure:
    flag[0] |
            |- indicates the status of compare flags 11-equal 10- regd>res2 01- regd<res2 00-invalid
    flag[1] |
    flag[2] - indicates any error
    remaining is empty until i find there is any use or necessity
*/
char temp[10];
char zero_reg[4];
int reg[5]={0,0,0,0,0};
int get_reg_no(char * oper)
 {
 	if(!(strcmp(oper,"001")))
 	  return 1;
 	else if(!(strcmp(oper,"010")))
 	  return 2;
 	else if(!(strcmp(oper,"011")))
 	  return 3;
 	  else if(!(strcmp(oper,"100")))
 	  return 4;
 	  else if(!strcmp(oper,"101"))
 	   return 5;
 	  else if(!strcmp(oper,""))
 	  return 0;
 }
 void compare(char * regd, char * regs2)
 	{
 		int indxd=get_reg_no(regd);
 		int indxs2=get_reg_no(regs2);
 		if(reg[indxd]==reg[indxs2])
 			{
 			//	printf("\nBoth numbers are equal!!");
 				flag[0]=1;
 				flag[1]=1;
 			}
 		else if(reg[indxd]>reg[indxs2])
 			{
 			//	printf("\nregd greater than regs2");
 				flag[0]=1;
 				flag[1]=0;
 			}
 		else if(reg[indxd]<reg[indxs2])
 			{
 			//	printf("\nregs2 greater than regd");
 				flag[0]=0;
 				flag[1]=1;
 			}
 	
 	}
void prnt_reg_values()
 	{
 		int i,j;
 		printf("\n=========================================================================");
 		printf("\n\nRegister values");
 		for(i=65,j=1;i<=68;i++,j++)
 			{
 			
 				printf("\nREGISTER %c=%d",i,reg[j]);
 			}
 		printf("\n=========================================================================");
 		printf("\n\n\n=========================================================================");
 		printf("\n\nFLAG STATUS");
 		printf("\n| FLAG INDEX  |");
 		for(i=0;i<8;i++)
 			{
 				printf("| %d |",i);
 			}
 		printf("\n| FLAG VALUES |");
 		for(i=0;i<8;i++)
 		   printf("| %d |",flag[i]);
 		   
 	}
int todecimal(unsigned long int n)
  {
  	
  	int decimal=0, i=0, rem;
    while (n!=0)
    
    {
        rem = n%10;
        n/=10;
        decimal += rem*pow(2,i);
        ++i;
    }
    return decimal;
  }
 void prnt_rslt_arith(char * mcode,char * regd,char * regs2,char * regs1,int rslt)
 	{
 		/* TODO (#2#): print results arithmetic
                   prnt_rslt_arith(...); */
 		printf("print results here...");
 	}
 int arith_op(char * mcode,char * regs1,char *regs2)
 	{
 		int indx1,indx2,rslt;
 	//	printf("\nArith_op\nmcode=%s regs1=%s regs2=%s",mcode,regs1,regs2);
 		if(!strcmp(mcode,"0100000"))
 			{
 				indx1=get_reg_no(regs1);
 				indx2=get_reg_no(regs2);
 				rslt=reg[indx1]+reg[indx2];
 				if(debug==1)
 					{
 						printf("\nREG %d + REG %d=%d\n",indx1,indx2,rslt);
 						printf("%d+%d=%d",reg[indx1],reg[indx2],rslt);
 					}
 				return rslt;
 			}
 		 else if(!strcmp(mcode,"0100001"))
 			{
 				indx1=get_reg_no(regs1);
 				indx2=get_reg_no(regs2);
 				rslt=reg[indx2]-reg[indx1];  //here by rule regs2 value will be assumed greater 
 				if(debug==1)
 					{
 						printf("\nREG %d - REG %d=%d\n",indx2,indx1,rslt);
 						printf("%d-%d=%d",reg[indx2],reg[indx1],rslt);
 					}
 				return rslt;
 			}
 		else if(!strcmp(mcode,"0100010"))
 			{
 				indx1=get_reg_no(regs1);
 				indx2=get_reg_no(regs2);
 				rslt=reg[indx2]*reg[indx1];   
 				if(debug==1)
 					{
 						printf("\nREG %d * REG %d=%d\n",indx1,indx2,rslt);
 						printf("%d*%d=%d",reg[indx1],reg[indx2],rslt);
 					}
 				return rslt;
 			}
 		 else if(!strcmp(mcode,"0100011"))
 			{
 				indx1=get_reg_no(regs1);
 				indx2=get_reg_no(regs2);
 				if(reg[indx1]==0)  
 					{
 						// division by zero error
 						printf("Division by zero error!!");exit(0);
 					}
 				else
 				   {
 				   		rslt=reg[indx2]/reg[indx1];
 				   		if(debug==1)
 						{
 								printf("\nREG %d / REG %d=%d\n",indx2,indx1,rslt);
 								printf("%d/%d=%d",reg[indx2],reg[indx1],rslt);
 						}
 				   		return rslt;
 				   }
 			}
 		   else if(!strcmp(mcode,"0100011"))
 			{
 				indx1=get_reg_no(regs1);
 				indx2=get_reg_no(regs2);
 				if(reg[indx1]==0)  
 					{
 						// division by zero error
 						printf("Division by zero error!!");exit(0);
 					}
 				else
 				   {
 				   		rslt=reg[indx2]%reg[indx1];
 				   		if(debug==1)
 						{
 								printf("\nREG %d % REG %d=%d\n",indx2,indx1,rslt);
 								printf("%d % %d=%d",reg[indx2],reg[indx1],rslt);
 						}
 				   		return rslt;
 				   }
 			}
 			
 	} 

main()
	{
		int i=0,j,imm_flg=0,len,indx;char ch;
		strcpy(zero_reg,"101");
		FILE *src,*dyn;
		src=fopen("BINARY.txt","r");
		if(!src)
			{
				printf("Error opening source code.Check for BINARY.txt file");exit(0);
			}
		dyn=fopen("DYNTAB.txt","r");
		if(!dyn)
		 {
		 	 printf("Error opening source code.Check for DYNTAB.txt file");exit(0);
		 }
	    for(i=0;i<8;i++)
	     flag[i]=-1;
	     i=0;int ctrdyn=0;
		while(!feof(src))
			{   int skip=0;
				//printf("\n\n\nExtracting codeline:%d",i);
				
				// Initialise all the strings else everything gets concatenated 
				strcpy(mcode,"");
			//	printf("\nmcode is initialised mcode=%s",mcode);
				strcpy(regd,"");
				strcpy(regs2,"");
				strcpy(regs1,"");
				immval=0;int firstbit=1;
				
					imm_flg=0;
				// extract mcode
				for(j=0;j<7;j++)
					{   int z;
						len=strlen(mcode);
						ch=getc(src);
						if(firstbit==1 && ch==49)
						 {
						 	char lbl[9];int lenb=0;int z=0;
						 	lenb=strlen(lbl);
						 	lbl[z]=ch;
						 	lbl[lenb+1]='\0';
						 	for(z=1;z<9;z++){
						 		ch=getc(src);
						 	//	ch=ch-48;
						 		lbl[z]=ch;
						 		lbl[z+1]='\0';
						 	}
						 //	printf("Labelbit is %s\n",lbl); 
						 	 skip=1;firstbit=0;
					
						     strcpy(dyntabds[ctrdyn].bin,"");
					
						     strcpy(dyntabds[ctrdyn].bin,lbl);
						  
						     dyntabds[ctrdyn].pos=ftell(src);
						 
						     ctrdyn++;
						  
						 	 break;
						 }
						 
					//	printf("\nchi=%d",ch);
					///	printf(" chc=%c",ch);
					//	ch=ch-48;
					//	printf("after sub\nchi=%d chc=%c",ch,ch);
						mcode[len]=ch;
					//	printf("\nmcode[%d]=%c",len,ch);
						mcode[len+1]='\0';
						firstbit=0;
					
					}
			    if(!skip) {
			    
				if(!strcmp(mcode,"0100111"))
					{
						imm_flg=1;
					//	printf("\nImmediate format found\n");
						//extract register number

						for(j=0;j<3;j++)
							{
								len=strlen(regd);
								ch=getc(src);
							
								regd[len]=ch;
								regd[len+1]='\0';
							}
						//extract the immediate value
						
						for(j=0;j<6;j++)	
							{
								ch=getc(src);
	      	  		 			ch=ch-48;
	      	  				//	 printf("\nch=%c",ch);
	      	  				//	 printf("\nimmval*10=%d",immval*10);
	      	   					immval*=10;
	      	  				//	  printf("\nimmval+%d=%d",ch,immval+ch);
	      	   					immval+=ch;
							}
						 int immint=todecimal(immval);
			            // printf("\n%s,%s,%d\n",mcode,regd,immint);
			             /* 
			              the code below does the mvi operation 
			              */
			              
			              //get the register number and save it in indx, the immediate value is stored in reg[indx]
			              indx=get_reg_no(regd);
			              reg[indx]=immint;
			            //  printf("The immdt value %d is moved to reg[%d]",immint,indx);
				
					}
					else if(!strcmp(mcode,"0100100"))
						{
							// mov register values
						//	printf("\nMove regsiter values instruction\n");
							for(j=0;j<3;j++)
							 	{
							 		len=strlen(regd);
							 		ch=getc(src);
							 		regd[len]=ch;
							 		regd[len+1]='\0';
							 	}
							for(j=0;j<3;j++)
								{
									getc(src); // to skip the first three zero's of the register value
								}
							for(j=0;j<3;j++)
								{
									len=strlen(regs2);
							 		ch=getc(src);
							 		regs2[len]=ch;
							 		regs2[len+1]='\0';
								}
							//	printf("\n%s %s %s",mcode,regd,regs2);
							// The trick here is to simply add a zero reg and the source reg and save result to dest reg
							//also we have to do this the machine code way :P
							strcpy(temp,"0100000");
							indx=get_reg_no(regd);
						    reg[indx]=arith_op(temp,zero_reg,regs2);
								
						}
				else if(!strcmp(mcode,"0100110"))
				 	{
				 		//	printf("Compare instruction");
				 			for(j=0;j<3;j++)
							 	{
							 		len=strlen(regd);
							 		ch=getc(src);
							 		regd[len]=ch;
							 		regd[len+1]='\0';
							 	}
							for(j=0;j<3;j++)
								{
									getc(src); // to skip the first three zero's of the register value
								}
							for(j=0;j<3;j++)
								{
									len=strlen(regs2);
							 		ch=getc(src);
							 		regs2[len]=ch;
							 		regs2[len+1]='\0';
								}
							//we have two registers....simply compare the values and set the flags
							/*
									00 - equal
									01 - regd < regs2
									10 - regd>regs2
									11 - invalid
							 */
							compare(regd,regs2);
				 			
				 	}
				else if(!strcmp(mcode,"0101000"))
					{   int z=0;long bincvt;unsigned long int posmv;
					//	printf("\nJump instruction");
						char ch;int i=0;int bin=0;
						ch=getc(src);
						ch=ch-48;           //here ch=ch-48 is required but not during assigning dyntabds[z].bin .see y
						bin*=10;
						bin+=ch;
						while(i<8)
						  {
						  	ch=getc(src);
	      	  		 	    ch=ch-48;
	      	  				//	 printf("\nch=%c",ch);
	      	  				//	 printf("\nimmval*10=%d",immval*10);
	      	   			    bin*=10;
	      	  				//	  printf("\nimmval+%d=%d",ch,immval+ch);
	      	   			    bin+=ch;i++;
						  }
					//	 printf("\nBinary is %09d",bin);
						 
						 for(z=0;z<ctrdyn;z++)
						   {
						   	
						   	//printf("string bin=%s\n",dyntabds[z].bin);
						   	sscanf(dyntabds[z].bin,"%ld",&bincvt);
						   //	bincvt=atoi(dyntabds[z].bin);
						  // 	printf("bincvt=%u\n",bincvt);
						   	if(bincvt==bin){
						   		posmv=dyntabds[z].pos;
						   		fseek(src,posmv,0);break;
						   	}
						   	  
						   }
					}	
					else if(!strcmp(mcode,"0101001"))
					{   int z=0;long bincvt;unsigned long int posmv;
					//	printf("\nJump if greater instruction");
						char ch;int i=0;int bin=0;
						ch=getc(src);
						ch=ch-48;           //here ch=ch-48 is required but not during assigning dyntabds[z].bin .see y
						bin*=10;
						bin+=ch;
						while(i<8)
						  {
						  	ch=getc(src);
	      	  		 	    ch=ch-48;
	      	  				//	 printf("\nch=%c",ch);
	      	  				//	 printf("\nimmval*10=%d",immval*10);
	      	   			    bin*=10;
	      	  				//	  printf("\nimmval+%d=%d",ch,immval+ch);
	      	   			    bin+=ch;i++;
						  }
					//	 printf("\nBinary is %09d",bin);
						 
						 for(z=0;z<ctrdyn;z++)
						   {
						   	
						   	//printf("string bin=%s\n",dyntabds[z].bin);
						   	sscanf(dyntabds[z].bin,"%ld",&bincvt);
						   //	bincvt=atoi(dyntabds[z].bin);
						 //  	printf("bincvt=%u\n",bincvt);
						   	if(bincvt==bin && flag[1]>flag[0] ){
						   		posmv=dyntabds[z].pos;
						   		fseek(src,posmv,0);break;
						   	}
						   	  
						   }
						   flag[0]=0;flag[1]=0;
					}
					else if(!strcmp(mcode,"0101010"))
					{   int z=0;long bincvt;unsigned long int posmv;
					//	printf("\nJump if greater or equal instruction");
						char ch;int i=0;int bin=0;
						ch=getc(src);
						ch=ch-48;           //here ch=ch-48 is required but not during assigning dyntabds[z].bin .see y
						bin*=10;
						bin+=ch;
						while(i<8)
						  {
						  	ch=getc(src);
	      	  		 	    ch=ch-48;
	      	  				//	 printf("\nch=%c",ch);
	      	  				//	 printf("\nimmval*10=%d",immval*10);
	      	   			    bin*=10;
	      	  				//	  printf("\nimmval+%d=%d",ch,immval+ch);
	      	   			    bin+=ch;i++;
						  }
					//	 printf("\nBinary is %09d",bin);
						 
						 for(z=0;z<ctrdyn;z++)
						   {
						   	
						   	//printf("string bin=%s\n",dyntabds[z].bin);
						   	sscanf(dyntabds[z].bin,"%ld",&bincvt);
						   //	bincvt=atoi(dyntabds[z].bin);
						//   	printf("bincvt=%u\n",bincvt);
						   	if(bincvt==bin && (flag[0]>flag[1] || flag[1]==flag[0]) ){
						   		posmv=dyntabds[z].pos;
						   		fseek(src,posmv,0);break;
						   	}
						   	  
						   }
						   flag[0]=0;flag[1]=0;
					}
						else if(!strcmp(mcode,"0101011"))
					{   int z=0;long bincvt;unsigned long int posmv;
					//	printf("\nJump if lesser instruction");
						char ch;int i=0;int bin=0;
						ch=getc(src);
						ch=ch-48;           //here ch=ch-48 is required but not during assigning dyntabds[z].bin .see y
						bin*=10;
						bin+=ch;
						while(i<8)
						  {
						  	ch=getc(src);
	      	  		 	    ch=ch-48;
	      	  				//	 printf("\nch=%c",ch);
	      	  				//	 printf("\nimmval*10=%d",immval*10);
	      	   			    bin*=10;
	      	  				//	  printf("\nimmval+%d=%d",ch,immval+ch);
	      	   			    bin+=ch;i++;
						  }
					//	 printf("\nBinary is %09d",bin);
						 
						 for(z=0;z<ctrdyn;z++)
						   {
						   	
						   	//printf("string bin=%s\n",dyntabds[z].bin);
						   	sscanf(dyntabds[z].bin,"%ld",&bincvt);
						   //	bincvt=atoi(dyntabds[z].bin);
						//   	printf("bincvt=%u\n",bincvt);
						   	if(bincvt==bin && flag[1]<flag[0] ){
						   		posmv=dyntabds[z].pos;
						   		fseek(src,posmv,0);break;
						   	}
						   	  
						   }
						   flag[0]=0;flag[1]=0;
					}		
						else if(!strcmp(mcode,"0101100"))
					{   int z=0;long bincvt;unsigned long int posmv;
					//	printf("\nJump if lesser or equal instruction");
						char ch;int i=0;int bin=0;
						ch=getc(src);
						ch=ch-48;           //here ch=ch-48 is required but not during assigning dyntabds[z].bin .see y
						bin*=10;
						bin+=ch;
						while(i<8)
						  {
						  	ch=getc(src);
	      	  		 	    ch=ch-48;
	      	  				//	 printf("\nch=%c",ch);
	      	  				//	 printf("\nimmval*10=%d",immval*10);
	      	   			    bin*=10;
	      	  				//	  printf("\nimmval+%d=%d",ch,immval+ch);
	      	   			    bin+=ch;i++;
						  }
						// printf("\nBinary is %09d",bin);
						 
						 for(z=0;z<ctrdyn;z++)
						   {
						   	
						   	//printf("string bin=%s\n",dyntabds[z].bin);
						   	sscanf(dyntabds[z].bin,"%ld",&bincvt);
						   //	bincvt=atoi(dyntabds[z].bin);
						  // 	printf("bincvt=%u\n",bincvt);
						   	if(bincvt==bin && (flag[1]<flag[0] || flag[1]==flag[0]) ){
						   		posmv=dyntabds[z].pos;
						   		fseek(src,posmv,0);break;
						   	}
						   	  
						   }
						   flag[0]=0;flag[1]=0;
					}										
 				else
					{
							//arithemetic instruction format
							//extract destination register value
						 
						for(j=0;j<3;j++)
								{
									len=strlen(regd);
									ch=getc(src);
								    regd[len]=ch;
									regd[len+1]='\0';
									
								}
							//extract source 2 register value - the bigger values in subtraction operation is here
						
							for(j=0;j<3;j++)
								{
									len=strlen(regs2);
									ch=getc(src);
								    regs2[len]=ch;
									regs2[len+1]='\0';
									
								}
								//extract source register value
							for(j=0;j<3;j++)
								{
									len=strlen(regs1);
									ch=getc(src);
								
									regs1[len]=ch;
									regs1[len+1]='\0';
								}
								
							//		printf("\n%s,%s,%s,%s\n",mcode,regd,regs2,regs1);
									
						/*
							Now, since we got all the required things lets do the operation!! 
							Here are the arithmetic mcodes for a quick refernce
							add		0100000
							sub		0100001
							mul		0100010
							div		0100011
							mod		0100101
							
						*/
						indx=get_reg_no(regd);
						reg[indx]=arith_op(mcode,regs1,regs2);
					//	printf("reg %d=%d \n regd=%s",indx,reg[indx],regd);
					//	prnt_rslt_arith(mcode,regd,regs2,regs1,reg[indx]);
						
							
					}
			i+=16;		
			}
		}
			fclose(src);
			prnt_reg_values();
			getchar();
	 	
	}


