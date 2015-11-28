#include<stdio.h>
#include<string.h>
void check_lb();
void check_opcd();
void R_line_1();
struct opcodetab//CREATION OF OPCODE TABLE
{
    char  code[10],objcode[10];
}myopcodetab[5]={
                   {"LDAA","00"},
                   {"JMAP","01"},
                   {"STAA","02"},
                    {"WORD","03"}
                    };


struct symbol_tab{//CREATION OF SYMBOL TABLE
                    char symbol[10];
                    int addr;
              }mysymbol_tab[10];

int startaddress,loc_ctr,sym_count=0,length;
char line_1[20],lbl[8],opcode[8],operand[8],programmename[10];

           void ps_1()//START OF PASS 1:------------------------------------
                  {
                       FILE *input,*inter,*fp;
                       char ch;
                        printf("\n\n...THE CONTENTS OF INPUTED FILE IS...\n\n");//PRINTING OF INPUT FILE
                        fp=fopen("INPUT.txt","r");
                        ch=fgetc(fp);
                    while(ch!=EOF)
                        {
                            printf("%c",ch);
                            ch=fgetc(fp);
                        }
                            printf("\n");

                       input=fopen("INPUT.txt","r");
                       inter=fopen("INTERMEDIATE.txt","w");
                       printf("\n---FILE AFTER ADDRESSING IS---\n");//PRINTING OF INTERMEDIATE FILE
                        printf("\nLOCATION_LABEL\tOPERAND\tOPCODE\n");
                    printf("_____________________________________");
                        fgets(line_1,20,input);

                      R_line_1();

                     if(!strcmp(opcode,"START"))
                      {

                       startaddress=atoi(operand);
                       loc_ctr=startaddress;
                      strcpy(programmename,lbl);

                        fprintf(inter,"%s",line_1);
                       fgets(line_1,20,input);
                       }
                      else
                      {
                          programmename[0]='\0';
                          startaddress=0;
                          loc_ctr=0;
                      }
                         printf("\n %d\t %s\t%s\t %s",loc_ctr,lbl,opcode,operand);

                           while(strcmp(line_1,"END")!=0)
                          {

                                   R_line_1();
                                   printf("\n %d\t %s \t%s\t %s",loc_ctr,lbl,opcode,operand);
                                   if(lbl[0]!='\0')check_lb();
                                   check_opcd();
                                   fprintf(inter,"%s %s %s\n",lbl,opcode,operand);
                                   fgets(line_1,20,input);
                          }

                   printf("\n %d\t\t%s",loc_ctr,line_1);
                   fprintf(inter,"%s",line_1);

                    fclose(inter);
                    fclose(input);
                      }

          void ps_2()//START OF PASS 2:------------------------------------
          {
                FILE *inter,*output;
                char record[30],part[8],value[5];
                int currenttxtln=0,fndopcode,foundoperand,check1,oprand_address,recaddress=0;
                inter=fopen("INTERMEDIATE.txt","r");
                output=fopen("OUTPUT.txt","w");
                fgets(line_1,20,inter);

                R_line_1();
                if(!strcmp(opcode,"START")) fgets(line_1,20,inter);
               printf("\n\n...CORRESSPONDING OBJECT CODE IS...\n");//PRINTING OF OBJECT CODE
               printf("\nH^ %s ^ %d ^ %d ",programmename,startaddress,length);//FOR HEADER RECORD
               fprintf(output,"\nH^ %s ^ %d ^ %d ",programmename,startaddress,length);
               recaddress=startaddress; record[0]='\0';
               while(strcmp(line_1,"END")!=0)
                        {
                                oprand_address=foundoperand=fndopcode=0;
                                value[0]=part[0]='\0';
                                R_line_1();
            for(check1=0;check1<3;check1++)
             {
               if(!strcmp(opcode,myopcodetab[check1].code))
               {
               fndopcode=1;
               strcpy(part,myopcodetab[check1].objcode);

             if(operand[0]!='\0')
             {
             for(check1=0;check1<sym_count;check1++)

             if(!strcmp(mysymbol_tab[check1].symbol,operand))
             {
             itoa(mysymbol_tab[check1].addr,value,10);
             strcat(part,value);
             foundoperand=1;
             }
              if(!foundoperand)strcat(part,"err");
              }
              }
              }
               if(!fndopcode)
               {
                               if(strcmp(opcode,"BYTE")==0||strcmp(opcode,"WORD")||strcmp(opcode,"RESB"))
                               {
                                   strcat(part,operand);
                              }
               }
               if((currenttxtln+strlen(part))<=8)
               {
                strcat(record,"^");
                strcat(record,part);

                currenttxtln=currenttxtln+strlen(part);
               }
                else
                {
                 printf("\nT^ %d ^%d %s",recaddress,currenttxtln/2,record);//FOR TEXT RECORD
                 fprintf(output,"\nT^ %d ^%d %s",recaddress,currenttxtln/2,record);
                 recaddress+=currenttxtln/2;
                 currenttxtln=strlen(part);
                 strcpy(record,part);

                }
          fgets(line_1,20,inter);
                }
                      printf("\nT^%d ^%d %s",recaddress,currenttxtln/2,record);
                      fprintf(output,"\nT^ %d ^%d %s",recaddress,currenttxtln/2,record);
                      printf("\nE^ %d\n",startaddress);//FOR END RECORD
                      fprintf(output,"\nE^ %d\n",startaddress);
                      fclose(inter);
                      fclose(output);
       }

       void R_line_1()
       {
            char buff[8],word1[8],word2[8],word3[8];
            int i,j=0,count=0;
             lbl[0]=opcode[0]=operand[0]=word1[0]=word2[0]=word3[0]='\0';
                 for(i=0;line_1[i]!='\0';i++)
                      {
                   if(line_1[i]!=' ')buff[j++]=line_1[i];
                   else
                      {
                     buff[j]='\0';
                     strcpy(word3,word2);strcpy(word2,word1);strcpy(word1,buff);
                     j=0;count++;
                      }
                      }
                      buff[j-1]='\0';
                      strcpy(word3,word2);
                      strcpy(word2,word1);
                      strcpy(word1,buff);
                    switch(count)
                       {
                            case 0:strcpy(opcode,word1);break;
                            case 1:{strcpy(opcode,word2);strcpy(operand,word1);}break;
                            case 2:{strcpy(lbl,word3);strcpy(opcode,word2);strcpy(operand,word1);}break;
                       }
                       }

            void check_lb()//CHECK FOR SYMBOL TABLE
                  {
                       int k,dupsy=0;
                     for(k=0;k<sym_count;k++)
                     if(!strcmp(lbl,mysymbol_tab[k].symbol))
                     {
                                                          mysymbol_tab[k].addr=-1;
                                                          dupsy=1;
                                                          break;
                                                          }
               if(!dupsy)
               {
               strcpy(mysymbol_tab[sym_count].symbol,lbl);
               mysymbol_tab[sym_count++].addr=loc_ctr;
                }
                }

  void check_opcd()//CHECK FOR OPCODE TABLE
         {

          int l=0,found=0;
          for(l=0;l<3;l++)


                          if(!strcmp(opcode,myopcodetab[l].code))
                          {

                                                     loc_ctr+=3;
                                                     found=1;
                                                     break;
                           }
              if(!found)
              {
                        if(!strcmp( opcode,"WORD")) loc_ctr+=3;
                        else if (!strcmp(opcode,"RESW"))loc_ctr+=(3*atoi(operand));
                        else if(!strcmp(opcode,"RESB"))loc_ctr+=atoi(operand);
               }
    }
  int main()
                    {

                            int i;
                            ps_1();//CALLING OF PASS 1
                            length=loc_ctr-startaddress;
                            printf("\t\n\n");
                          printf("\n\n...THE symbol_tab IS...\n\n");//PRINTING OF SYMBOL TABLE
                         for(i=0;i<4;i++)
                        {
                            printf("%s\t%d\n",mysymbol_tab[i].symbol,mysymbol_tab[i].addr);
                        }
                        ps_2();//CALLING OF PASS 2
                    }

