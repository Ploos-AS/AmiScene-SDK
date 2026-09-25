#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "amicopper.h"
static int eq(const char*a,const char*b){while(*a&&*b){if(toupper((unsigned char)*a++)!=toupper((unsigned char)*b++))return 0;}return !*a&&!*b;}
int AmiCopperRexxCommand(struct AmiCopperDocument *doc,const char *command,char *result,unsigned int n,int *quit)
{
 char buf[320],*verb,*arg; unsigned long bad=0; if(!doc||!command||!result||!n)return 20; strncpy(buf,command,sizeof(buf)-1);buf[sizeof(buf)-1]=0;verb=strtok(buf," \t\r\n");arg=strtok(0,"\r\n");while(arg&&(*arg==' '||*arg=='\t'))arg++;result[0]=0;if(quit)*quit=0;if(!verb)return 10;
 if(eq(verb,"VERSION")){snprintf(result,n,"%s API %d",AMICOPPER_NAME,AMICOPPER_API_VERSION);return 0;}
 if(eq(verb,"STATUS")){snprintf(result,n,"%s %s instructions=%lu selected=%lu",doc->dirty?"DIRTY":"CLEAN",doc->valid?"VALID":"UNVALIDATED",doc->instruction_count,doc->selected);return 0;}
 if(eq(verb,"VALIDATE")){if(AmiCopperDocumentValidate(doc,&bad)){snprintf(result,n,"VALID");return 0;}snprintf(result,n,"INVALID index=%lu",bad);return 5;}
 if(eq(verb,"OPEN")){if(!arg||!*arg)return 10;if(!AmiCopperDocumentLoad(doc,arg)){snprintf(result,n,"OPEN_FAILED");return 10;}snprintf(result,n,"OK");return 0;}
 if(eq(verb,"SAVE")){const char*p=(arg&&*arg)?arg:doc->path;if(!p||!AmiCopperDocumentSave(doc,p)){snprintf(result,n,"SAVE_FAILED");return 10;}snprintf(result,n,"OK");return 0;}
 if(eq(verb,"QUIT")){if(quit)*quit=1;snprintf(result,n,"OK");return 0;}
 snprintf(result,n,"UNKNOWN_COMMAND");return 10;
}
