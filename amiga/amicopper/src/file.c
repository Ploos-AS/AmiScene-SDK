#include <stdio.h>
#include <string.h>
#include "amicopper.h"
#include "amicopper_copper.h"

int AmiCopperDocumentLoad(struct AmiCopperDocument *doc,const char *path)
{
 FILE *f; char line[160]; unsigned short w0,w1; struct AmiCopperDocument tmp;
 if(!doc||!path||(f=fopen(path,"r"))==0)return 0; AmiCopperDocumentInit(&tmp);
 while(fgets(line,sizeof(line),f)){char *p=line;while(*p==' '||*p=='\t')p++;if(!*p||*p=='\n'||*p==';')continue;if(!AmiCopperParseLine(p,&w0,&w1)||tmp.instruction_count>=AMICOPPER_MAX_INSTRUCTIONS){fclose(f);return 0;}tmp.words[tmp.instruction_count][0]=w0;tmp.words[tmp.instruction_count][1]=w1;tmp.instruction_count++;}
 fclose(f); if(!AmiCopperDocumentValidate(&tmp,0))return 0; *doc=tmp; strncpy(doc->path,path,sizeof(doc->path)-1); doc->path[sizeof(doc->path)-1]=0; doc->dirty=0; return 1;
}
int AmiCopperDocumentSave(struct AmiCopperDocument *doc,const char *path)
{
 FILE *f; unsigned long i; char line[96]; struct AmiCopperInstruction ins;
 if(!doc||!path||(f=fopen(path,"w"))==0)return 0;
 fputs("; AmiCopper source\n",f); for(i=0;i<doc->instruction_count;i++){AmiCopperDecode(doc->words[i][0],doc->words[i][1],&ins);if(!AmiCopperFormatSource(&ins,line,sizeof(line))){fclose(f);return 0;}fprintf(f,"%s\n",line);} if(fclose(f)!=0)return 0; strncpy(doc->path,path,sizeof(doc->path)-1); doc->path[sizeof(doc->path)-1]=0; doc->dirty=0; return 1;
}
