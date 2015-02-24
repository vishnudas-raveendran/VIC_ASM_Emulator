#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int debug=0;
struct OPTABDS
 {
 	char opcode[10];
 	int mcode; // machine code equivalent of opcode
 	int nop; // no of valid operands
 }optab[14];
 struct dyntabds
 {
 	char label[50];
 	unsigned long bin;
 }dyntabds[10];
 
unsigned long tobin(int intgr)
 {
 	 int bin[16],tmp[16];int i=0,j,k;
 	 unsigned long binary=0;
 	 while(intgr!=0){
        bin[i]=intgr%2;
      //  printf("bin[%d]=%d",i,bin[i]);
        intgr=intgr/2;
        i++;
      }i--;
     // printf("bin[%d]=%d",i,bin[i]);
      for(j=0;i>=0;i--,j++)
       {
       	 tmp[j]=bin[i];
       }j--;
       for(i=0;i<=j;i++)
        {
            binary*=10;
          //  printf("\ntmp[%d]=%d",i,tmp[i]);
            binary+=tmp[i];
        }
      //  printf("\n%06ld",binary);
      return binary;
 }
 convert_to_bin()
  {
  	   printf("\n\nConverting the Source code to binary with memory address....");
  	   char ch,opcode[8];int i,len,oper[4]={0,0,0,0},flg_reg[16]={0,0,0,0},mcode,mem=0,inc=16,op3=0,nop=0,opflg=0,lbl_cnt=0;
  	   int ctr_dyntab=0;
  	   int jmp=0,imm=0;          // assign jmp flag=1 for jump statement goto  -- pending
  	   	unsigned long immop,bin_lbl;						// assign imm flag=1 for mvi statement, immop=immediate operand
  	   strcpy(opcode,"");
  	   FILE *fp;FILE *bin_wr;FILE *mbin,*dyntab;
  	   printf("\n\nCreating the BINARY_MEM.txt file...\n\n");
       bin_wr=fopen("BINARY_MEM.txt","w");
  	   if(!bin_wr)
  	    {
  	    	 printf("Error creating file!!");
  	    }
  	   dyntab=fopen("DYNTAB.txt","w");
  	   if(!dyntab)
  	    {
  	    	printf("Error creating dynamic table!!");
  	    }
  	   fp=fopen("ASMCODE.vic","r");
  	   if(!fp)
  	   {
  	   	 printf("Error opening ASMCODE.vic file");
  	   }
  	   mbin=fopen("BINARY.txt","w");
  	   if(!mbin)
  	    {
  	    	 printf("Error creating file!!");
  	    }
  	  while(!feof(fp))
  	   {
  	   	 ch=getc(fp);
  	   //	 printf("\nch=%c",ch);
  	   //	 getch();
  	   	 len=strlen(opcode);
  	   	 if(ch=='#')
  	   	  {
  	   	  	   char label[20];
  	   	  	   strcpy(label," ");
  	   	  	   ch=getc(fp);
  	   	  	   while(ch!=':')
  	   	  	    {
  	   	  	    	
  	   	  	    	len=strlen(label);
  	   	  	    	label[len]=ch;
  	   	  	    	label[len+1]='\0';
  	   	  	    	ch=getc(fp);
  	   	  	    	
  	   	  	    }
  	   	  	    lbl_cnt++;
  	   	  	  //  printf("lbl_Cnt=%d",lbl_cnt);
			        unsigned long bin_lbl=tobin(lbl_cnt); 
			        bin_lbl+=100000000;
			        //write to dynamic table
			        fprintf(dyntab,"%s %09d\n",label,bin_lbl);
  	     	        fprintf(bin_wr,"%04d ",mem);
  	     	        fprintf(bin_wr,"%09d\n",bin_lbl);
       	  	        //fprintf(mbin,"1");
       	  	        fprintf(mbin,"%09d",bin_lbl);
       	  	        strcpy(dyntabds[ctr_dyntab].label,label);
       	  	         dyntabds[ctr_dyntab].bin=bin_lbl;
       	  	       //  printf("dyntabds[%d].label=%s\ndyntabds[%d].bin=%08d",ctr_dyntab,dyntabds[ctr_dyntab].label,ctr_dyntab,dyntabds[ctr_dyntab].bin);
  	   	  	        mem+=inc;ctr_dyntab++;
  	   	  }
  	   	 else if(ch==';')
  	   	  { 
  	   // search the OPTAB data structure for the opcode equivalent binary
  	   for(i=0;i<10;i++)
  	    {     
  	    	 if(!(strcmp(opcode,optab[i].opcode)))
  	    	  {
  	    	   //	printf("Eq=%07d",optab[i].mcode);
  	    	    opflg=1;        // opcode found in the OPTAB
  	    	    mcode=optab[i].mcode;
  	    	    nop=optab[i].nop;
  	    	  }
  	    	  
  	    }
  	    
  	    if(!opflg)
  	     {
  	     	printf("\n Error: Opcode \"%s\" not found in OPTAB at memory address %04d",opcode,mem);exit(0);
  	     }
  	    if(debug){
  	     printf("\nINSTRUCTION:\n");
  	   printf("\nOpcode:%s",opcode);
  	   printf("\noperand1\topernad2\toperand3\n");
  	    printf("\n%03d\t\t%03d\t\t%03d",oper[0],oper[1],oper[2]);
  	    printf("\nFlag registers:");
  	    printf("\nError flag:%d ",flg_reg[0]);
  	    printf("Comparison flag:%d%d",flg_reg[1],flg_reg[2]);
  	    printf(" Zero flag:%d",flg_reg[3]);
  	    printf("\n"); 
       	}
       	
       	// Print the machine code to BINARY_MEM.TXT
       	if((nop==2)&& imm==1)
       	  {
       	  	if(!fprintf(bin_wr,"%04d 0100111 %03d %06ld\n",mem,oper[0],immop))
       	    {
       	     printf("\nError writing machine code to BINARY_MEM.txt file");
       	    }
       	    if(!fprintf(mbin,"0100111%03d%06ld",oper[0],immop))
       	    {
       	     printf("\nError writing machine code to BINARY.txt file");
       	    }
       	    imm=0;
       	  }
       	 else if(nop==3){
       	 	
       	   if(!fprintf(bin_wr,"%04d %07d %03d %03d %03d\n",mem,mcode,oper[0],oper[1],oper[2]))
       	    {
       	     printf("\nError writing machine code to BINARY_MEM.txt file");
       	    }
       		if(!fprintf(mbin,"%07d%03d%03d%03d",mcode,oper[0],oper[1],oper[2]))
       	    {
       	     printf("\nError writing machine code to BINARY.txt file");
       	    }
       	
       	  
          }
          else if(nop==2)
           {
           	  fprintf(bin_wr,"%04d %07d %03d %06d\n",mem,mcode,oper[0],oper[1]);
           	  fprintf(mbin,"%07d%03d%06d",mcode,oper[0],oper[1]);
           }
       /*	 else if(nop==1)
       	  {
       	  	 fprintf(bin_wr,"%04d %07d %09d\n",mem,mcode,oper[0]);
       	  	 fprintf(mbin,"%07d%09d",mcode,oper[0]);
       	  }*/
       
  	    //reinitialise the values to read the next instruction.
  	    strcpy(opcode,"");
  	   	  	len=strlen(opcode);
  	   	  	op3=0;
  	   	  	mem+=inc;
  	   	    opflg=0;         // reinitialise the opcode found flag
  	   	   
  	   }
  	   else if(!strcmp(opcode,"jmp"))
  	    {
  	    	char label[50];unsigned long binlab=0;
  	    	 strcpy(label," ");
  	    	 ch=getc(fp);
  	    	while(ch!=';')
  	    	 {
  	    	 	
  	   	  	    	len=strlen(label);
  	   	  	    	label[len]=ch;
  	   	  	    	label[len+1]='\0';
				    ch=getc(fp);
  	    	 }
  	    	for(i=0;i<ctr_dyntab;i++)
  	    	 {
  	    	   	if(!strcmp(label,dyntabds[i].label))
  	    	   	  {
  	    	   	  	   binlab=dyntabds[i].bin;
  	    	   	  //	   printf("Match found!! %09d",binlab);
					   break;
  	    	   	  }
  	    	 }
  	    	 fprintf(bin_wr,"%04d 0101000 %09d\n",mem,binlab);
       	  	 fprintf(mbin,"0101000%09d",binlab);
  	         strcpy(opcode,"");
  	    }
  	    else if(!strcmp(opcode,"jmg"))
  	    {
  	    	char label[50];unsigned long binlab=0;
  	    	 strcpy(label," ");
  	    	 ch=getc(fp);
  	    	while(ch!=';')
  	    	 {
  	    	 	
  	   	  	    	len=strlen(label);
  	   	  	    	label[len]=ch;
  	   	  	    	label[len+1]='\0';
				    ch=getc(fp);
  	    	 }
  	    	for(i=0;i<ctr_dyntab;i++)
  	    	 {
  	    	   	if(!strcmp(label,dyntabds[i].label))
  	    	   	  {
  	    	   	  	   binlab=dyntabds[i].bin;
  	    	   	  //	   printf("Match found!! %09d",binlab);
					   break;
  	    	   	  }
  	    	 }
  	    	 fprintf(bin_wr,"%04d 0101001 %09d\n",mem,binlab);
       	  	 fprintf(mbin,"0101001%09d",binlab);
  	         strcpy(opcode,"");
  	    }
  	    else if(!strcmp(opcode,"jge"))
  	    {
  	    	char label[50];unsigned long binlab=0;
  	    	 strcpy(label," ");
  	    	 ch=getc(fp);
  	    	while(ch!=';')
  	    	 {
  	    	 	
  	   	  	    	len=strlen(label);
  	   	  	    	label[len]=ch;
  	   	  	    	label[len+1]='\0';
				    ch=getc(fp);
  	    	 }
  	    	for(i=0;i<ctr_dyntab;i++)
  	    	 {
  	    	   	if(!strcmp(label,dyntabds[i].label))
  	    	   	  {
  	    	   	  	   binlab=dyntabds[i].bin;
  	    	   	  //	   printf("Match found!! %09d",binlab);
					   break;
  	    	   	  }
  	    	 }
  	    	 fprintf(bin_wr,"%04d 0101010 %09d\n",mem,binlab);
       	  	 fprintf(mbin,"0101010%09d",binlab);
  	         strcpy(opcode,"");
  	    }
  	    else if(!strcmp(opcode,"jml"))
  	    {
  	    	char label[50];unsigned long binlab=0;
  	    	 strcpy(label," ");
  	    	 ch=getc(fp);
  	    	while(ch!=';')
  	    	 {
  	    	 	
  	   	  	    	len=strlen(label);
  	   	  	    	label[len]=ch;
  	   	  	    	label[len+1]='\0';
				    ch=getc(fp);
  	    	 }
  	    	for(i=0;i<ctr_dyntab;i++)
  	    	 {
  	    	   	if(!strcmp(label,dyntabds[i].label))
  	    	   	  {
  	    	   	  	   binlab=dyntabds[i].bin;
  	    	   	  //	   printf("Match found!! %09d",binlab);
					   break;
  	    	   	  }
  	    	 }
  	    	 fprintf(bin_wr,"%04d 0101011 %09d\n",mem,binlab);
       	  	 fprintf(mbin,"0101011%09d",binlab);
  	         strcpy(opcode,"");
  	    }
  	    else if(!strcmp(opcode,"jle"))
  	    {
  	    	char label[50];unsigned long binlab=0;
  	    	 strcpy(label," ");
  	    	 ch=getc(fp);
  	    	while(ch!=';')
  	    	 {
  	    	 	
  	   	  	    	len=strlen(label);
  	   	  	    	label[len]=ch;
  	   	  	    	label[len+1]='\0';
				    ch=getc(fp);
  	    	 }
  	    	for(i=0;i<ctr_dyntab;i++)
  	    	 {
  	    	   	if(!strcmp(label,dyntabds[i].label))
  	    	   	  {
  	    	   	  	   binlab=dyntabds[i].bin;
  	    	   	  //	   printf("Match found!! %09d",binlab);
					   break;
  	    	   	  }
  	    	 }
  	    	 fprintf(bin_wr,"%04d 0101100 %09d\n",mem,binlab);
       	  	 fprintf(mbin,"0101100%09d",binlab);
  	         strcpy(opcode,"");
  	    }
	   /* else if(ch==':')
  	     {
  	     	//jump label found, lbl_Cnt assigns a unique code to every label
  	     	 lbl_cnt++;
			 unsigned long bin_lbl=tobin(lbl_cnt); 
  	     	 mcode=0101000;
  	     	 nop=0;
  	     	 fprintf(bin_wr,"%04d 1",mem);
  	     	 fprintf(bin_wr,"%08d\n",bin_lbl);
       	  	 fprintf(mbin,"1");
       	  	 fprintf(mbin,"%08d",bin_lbl);
       	  	 mem+=inc;
       	  	 op3=0;opflg=1;
       	  	 len=9;
       	  
  	     }    */                        //if(ch==';')
  	   	 else if(ch>=97&&ch<=122)
  	   	  {
  	   	  	 opcode[len]=ch;
  	   	  //	 printf("\nopcode[%d]=%c",len,opcode[len]);
  	   	  	 opcode[len+1]='\0';
  	   	  	 if(!(strcmp(opcode,"mvi")))
  	   	  	   {
  	   	  	   	 imm=1;  // immediate statement found flag raised
  	   	  	       
  	   	  	   }
  	   	  }
  	   	 /* else if(ch=' ')
  	   	   {
  	   	   	 continue;
  	   	   }*/
  	   	
  	   	  else if(ch==' ')
  	   	   {
  	   	   	   
  	   	   	    ch=getc(fp);
  	   	   	  //  printf("\nreached first operand:");
  	   	   	    if(ch=='A')
  	   	   	     {
  	   	   	     	oper[0]=1;
  	   	   	     }
  	   	   	    else if(ch=='B')
  	   	   	     { oper[0]=10;
  	   	   	     
  	   	   	     }
  	   	   	    else if(ch=='C')
  	   	   	     { oper[0]=11;
  	   	   	     }
  	   	   	    else if(ch=='D')
  	   	   	     {
  	   	   	     	oper[0]=100;
  	   	   	     }
  	   	   	     else if(!jmp)
  	   	   	      {
  	   	   	      	printf("\n Error: Register \" %c \" not found at memory address %04d",ch,mem);
  	   	   	      }
  	   	   }
  	   	   else if(ch==',' && op3==0)
  	   	    {
  	   	         
  	   	         //printf("\nch=%c",ch);
  	   	         if(imm)
  	   	          {
  	   	          	int i;
  	   	          	fscanf(fp,"%d",&i);
  	   	          //	printf("i=%d",i);
  	   	          	immop=tobin(i);
  	   	          //	printf("immop=%06ld",immop);
					continue;
  	   	          }
  	   	          	ch=getc(fp);
  	   	   	    if(ch=='A')
  	   	   	     {
  	   	   	     	oper[1]=1;
  	   	   	     }
  	   	   	    else if(ch=='B')
  	   	   	     { oper[1]=10;
  	   	   	     
  	   	   	     }
  	   	   	    else if(ch=='C')
  	   	   	     { oper[1]=11;
  	   	   	     }
  	   	   	    else if(ch=='D')
  	   	   	     {
  	   	   	     	oper[1]=100;
  	   	   	     }
  	   	   	     else if(!jmp)
  	   	   	      {
  	   	   	      	printf("\n Error: Register \" %c \" not found at memory address %04d",ch,mem);
  	   	   	      }
  	   	   	     op3=1; // Tell the assembler to consider the next register after comma to be the third operand
  	   	    }
  	     else if(ch==',' && op3==1)
  	   	    {
  	   	    	ch=getc(fp);
  	   	    //	printf("\nreached third operand");
  	   	   	    if(ch=='A')
  	   	   	     {
  	   	   	     	oper[2]=1;
  	   	   	     }
  	   	   	    else if(ch=='B')
  	   	   	     { oper[2]=10;
  	   	   	     
  	   	   	     }
  	   	   	    else if(ch=='C')
  	   	   	     { oper[2]=11;
  	   	   	     }
  	   	   	    else if(ch=='D')
  	   	   	     {
  	   	   	     	oper[2]=100;
  	   	   	     }
  	   	   	     else if(!jmp)
  	   	   	      {
  	   	   	      	printf("\n Error: Register \" %c \" not found at memory address %04d",ch,mem);
  	   	   	      }
  	   	   	     op3=0; // reinitialise the op3
  	   	    }
  	  
  	}
  	    fclose(fp);
  	    fclose(mbin);
  	    fclose(bin_wr);
  	    fclose(dyntab);
  }
 load_optab()
  {
  	FILE * opfr=NULL;int flg;int i=0;
     opfr=fopen("OPTAB.dat","r");
     printf("\nLoading the OPTAB...\n");
      
     while(fread(optab,1,sizeof(optab),opfr)&&i<=12)
       {
     //  	printf("reached here!!");
        optab[i].opcode;optab[i].mcode;optab[i].nop;
      // 	printf("\n%s",optab[i].opcode);
      //	printf("\t\t%d",optab[i].mcode);
      //	printf("\t\t\t%d",optab[i].nop);
       	i++;
       }
       printf("\nOPTAB loaded...");
       if(debug){
    
       	printf("\n|  OPCODE   |    mcode     |    No of operands    |\n");
       for(i=0;i<=12;i++)                // change i<3 to i<10 for 10 instructions
        {
        	 
        printf("\n%s",optab[i].opcode);
      	printf("\t\t%07d",optab[i].mcode);
       	printf("\t\t\t%d",optab[i].nop);
        }
       }
       fclose(opfr);
  }
 
  create_optab_file()
   {
   	 /* printf("In the create optab\n");
   	  int i;
  	 for(i=0;i<=12;i++)
  	  {
  	  	printf("\nmcode=%d ",optab[i].mcode);
  	  	printf("nop=%d",optab[i].nop);
  	  }*/
   	 FILE *opfile=NULL;
   	 opfile=fopen("OPTAB.txt","w");
   	 if(!opfile)
   	  {
   	  	printf("could not create OPTAB.txt file");
   	  	
   	  }
   	  else
   	   { int i;
   	   	  fprintf(opfile,"\n|OPCODE\t|   MACHINE CODE  |    No.of operands");
   	   	  for(i=0;i<=12;i++)
   	   	   {
   	   	   	  fprintf(opfile,"\n|%s\t|\t%07d\t  |\t\t%d    ",optab[i].opcode,optab[i].mcode,optab[i].nop);
   	   	   }
   	   	   fclose(opfile);
   	   }
   	  
   }
 initialise()
  {
  	printf("\n\nChecking for OPTAB file...");
  	FILE * opf=NULL;
  	opf=fopen("OPTAB.dat","r");
  	if(!opf)
  	 {
  	 	FILE * opfc=NULL;int flg;
  	    opfc=fopen("OPTAB.dat","w");
  	 	printf("\nOPTAB file does not exist!!\nCreating a new OPTAB file");
  	 	strcpy(optab[0].opcode,"add");
  	 	optab[0].mcode=100000;
  	 	optab[0].nop=3;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	printf("\n\nInitialising the OPTAB...");
  	 	strcpy(optab[1].opcode,"sub");
  	 	optab[1].mcode=100001;
  	 	optab[1].nop=3;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 	
  	 	strcpy(optab[2].opcode,"mul");
  	 	optab[2].mcode=100010;
  	 	optab[2].nop=3;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 	
  	 	strcpy(optab[3].opcode,"div");
  	 	optab[3].mcode=100011;
  	 	optab[3].nop=3;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 	strcpy(optab[4].opcode,"mov");
  	 	optab[4].mcode=100100;
  	 	optab[4].nop=2;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 	strcpy(optab[5].opcode,"mod");
  	 	optab[5].mcode=100101;
  	 	optab[5].nop=3;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 	strcpy(optab[6].opcode,"comp");
  	 	optab[6].mcode=100110;
  	 	optab[6].nop=2;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 	strcpy(optab[7].opcode,"mvi");
  	 	optab[7].mcode=100111;
  	 	optab[7].nop=2;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	
  	 //	strcpy(optab[8].opcode,"");
  	 	strcpy(optab[8].opcode,"jmp");
  	 	optab[8].mcode=101000;
  	 	optab[8].nop=1;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	strcpy(optab[9].opcode,"jmg");
  	 	optab[9].mcode=101001;
  	 	optab[9].nop=1;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	strcpy(optab[10].opcode,"jge");
  	 	optab[10].mcode=101010;
  	 	optab[10].nop=1;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	strcpy(optab[11].opcode,"jml");
  	 	optab[11].mcode=101011;
  	 	optab[11].nop=1;
  	 	printf("optab[11].mcode=%d",optab[11].mcode);
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	strcpy(optab[12].opcode,"jle");
  	 	optab[12].mcode=101100;
  	 	optab[12].nop=1;
  	 	flg=fwrite(optab,1,sizeof(optab),opfc);
  	 	if(!flg){
  	 		printf("\nError writing opcodes to file!");exit(1);
  	 	}
  	 	fclose(opfc);
  	 }
  	 
  	fclose(opf);
  }
printcode()
 {
   printf("\n\nReading the code from file...\n\n");
   FILE *codefl_rd = fopen("ASMCODE.vic", "r");
    if(!codefl_rd)
   	    {
   	    	printf("\nError opening code file: ASMCODE.txt");exit(1);
   	    }
    int ch;
     while (ch != EOF)
     {
       ch = getc(codefl_rd);
       putchar(ch);
     
      }
   fclose(codefl_rd);
   
   return 0;
 }
 assign_memaddr()
   {
   	  int ch;
   	  FILE *codefl_rd = fopen("ASMCODE.vic", "r");
   	   if(!codefl_rd)
   	    {
   	    	printf("\nError opening code file: ASMCODE.vic");exit(1);
   	    }
      FILE *memfl_wr=fopen("MEMCODE.txt","w");
        if(!memfl_wr)
   	    {
   	    	printf("\nError opening Memory addressed code file: MEMCODE.txt");exit(1);
   	    }
       printf("\n\nAssigning memory address to code (Address begins from 0000)...\n\n");
       int mem=0,inc=16, sc_flag=0;
       printf("%04d ",mem);
       fprintf(memfl_wr,"%04d ",mem);
      mem+=inc;
      ch = getc(codefl_rd);
     while (ch != EOF)
     {
       if(ch!='\n'){
       putchar(ch);
       putc(ch,memfl_wr);}
       if(ch==';' || ch==':')
        { 
           sc_flag=1;          //semi-colon flag, put mem addr in next line
	    }
	    if(sc_flag){
           sc_flag=0;
           printf("\n%04d ",mem);
          fprintf(memfl_wr,"\n%04d ",mem);
           mem+=inc;
		  // putc(ch,memfl_wr);
         }
         ch = getc(codefl_rd);
        // getch();
      }
   fclose(codefl_rd);
   fclose(memfl_wr);
   return 0;
   }
   verify_code()
     {
     	 
     }
main()
 {
 	printf("\n***************************************************************************\n");
 	printf("\n\t\t\tASSEMBLY LANGUAGE EMULATER\n\n");
 	printf("\n***************************************************************************\n\n");
 	printf("Please press enter to continue...");
 	getch();
   if(printcode())
    {
    	printf("Error printing the code!!");
    }
   if(assign_memaddr())
    {
    	printf("Error assigning memory addresses!!");
    }
   initialise();
    
   if(load_optab())
    {
    	printf("Error loading the optab");    }
    	
    create_optab_file();
    	
    if(convert_to_bin())
     {
     	printf("Error converting instructions to binary");
     }
     printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
     printf("\n----------------------Assembly completed successfully--------------------------\n");
     printf("\n||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n");
     printf("\nNOTE: Please run the binrun.exe to view the result of the instruction\n");
     getch();
  // verify_code();
   

 }
