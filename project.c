#include<stdio.h>
#include<string.h>
void chk_label();
 void chk_opcode();
 void READ_LINE();
struct optab
 {
     char   code[10],objcode[10];
 }myoptab[3]={
                    {"LDA","00"},
                    {"JMP","01"},
                    {"STA","02"}
              };


 struct symtab{
                     char symbol[10];
                     int addr;
               }mysymtab[10];

 int startaddr,locctr,symcount=0,length;
 char line[20],label[8],opcode[8],operand[8],programname[10];

 //                void PASS1()
                   {
                        FILE *input,*inter;
                        input=fopen("input.txt","r");
                        inter=fopen("inter.txt","w");
                         printf("LOCATION LABEL\tOPERAND\tOPCODE\n");
                         printf("_____________________________________");
                         fgets(line,20,input);

                       READ_LINE();

                      if(!strcmp(opcode,"START"))
                       {

                        startaddr=atoi(operand);
                        locctr=startaddr;
                       strcpy(programname,label);

                            fprintf(inter,"%s",line);
                        fgets(line,20,input);
                        }
                       else
                       {
                           programname[0]='\0';
                           startaddr=0;
                           locctr=0;
                       }
                          printf("\n %d\t %s\t%s\t %s",locctr,label,opcode,operand);

                            while(strcmp(line,"END")!=0)
                           {

                                    READ_LINE();
                                    printf("\n %d\t %s \t%s\t %s",locctr,label,opcode,operand);
                                    if(label[0]!='\0')chk_label();
                                    chk_opcode();
                                    fprintf(inter,"%s %s %s\n",label,opcode,operand);
                                    fgets(line,20,input);
                           }

                    printf("\n %d\t\t%s",locctr,line);
                    fprintf(inter,"%s",line);

                     fclose(inter);
                     fclose(input);
                       }
