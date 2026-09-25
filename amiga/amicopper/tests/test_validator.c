#include <stdio.h>
#include "amicopper.h"
static int add(struct AmiCopperDocument*d,const char*s){unsigned short a,b;if(!AmiCopperParseLine(s,&a,&b))return 0;return AmiCopperDocumentInsert(d,a,b);}
static int expect(int valid,const char **lines){struct AmiCopperDocument d;unsigned long bad=0;int i,r;AmiCopperDocumentInit(&d);for(i=0;lines[i];i++)if(!add(&d,lines[i]))return 0;r=AmiCopperDocumentValidate(&d,&bad);if(r!=valid){fprintf(stderr,"validator mismatch: expected %d got %d bad=%lu\n",valid,r,bad);return 0;}return 1;}
int main(void){const char *ok[]={"WAIT 44,2","MOVE COLOR00,$000f","END",0};const char *no_end[]={"WAIT 44,2",0};const char *after_end[]={"END","MOVE COLOR00,$000f",0};const char *backwards[]={"WAIT 100,0","WAIT 99,0","END",0};if(!expect(1,ok)||!expect(0,no_end)||!expect(0,after_end)||!expect(0,backwards))return 1;puts("AmiCopper validator PASS");return 0;}
