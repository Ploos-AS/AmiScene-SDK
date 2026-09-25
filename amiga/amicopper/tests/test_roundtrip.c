#include <stdio.h>
#include <string.h>
#include "amicopper.h"
#include "amicopper_copper.h"
static int check(const char *source){unsigned short a,b,c,d;struct AmiCopperInstruction ins;char out[96];if(!AmiCopperParseLine(source,&a,&b))return 0;if(!AmiCopperDecode(a,b,&ins))return 0;if(!AmiCopperFormatSource(&ins,out,sizeof(out)))return 0;if(!AmiCopperParseLine(out,&c,&d))return 0;if(a!=c||b!=d){fprintf(stderr,"round-trip failed: %s -> %s: %04x/%04x != %04x/%04x\n",source,out,a,b,c,d);return 0;}return 1;}
int main(void){const char *cases[]={"MOVE COLOR00,$000f","MOVE 0x180,0x0abc","WAIT 44,0","WAIT 100,40,63,126,0","SKIP 120,80,85,170,1","END",0};int i;for(i=0;cases[i];i++)if(!check(cases[i]))return 1;puts("AmiCopper parser/formatter round-trip PASS");return 0;}
