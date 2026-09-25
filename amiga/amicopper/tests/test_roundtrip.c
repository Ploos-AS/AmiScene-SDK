#include <stdio.h>
#include <string.h>
#include "amicopper.h"
#include "amicopper_copper.h"
static int check(const char *source){unsigned short a,b,c,d;struct AmiCopperInstruction ins;char out[96];if(!AmiCopperParseLine(source,&a,&b))return 0;if(!AmiCopperDecode(a,b,&ins))return 0;if(!AmiCopperFormatSource(&ins,out,sizeof(out)))return 0;if(!AmiCopperParseLine(out,&c,&d))return 0;if(a!=c||b!=d){fprintf(stderr,"round-trip failed: %s -> %s: %04x/%04x != %04x/%04x\n",source,out,a,b,c,d);return 0;}return 1;}
static int reject(const char *source){unsigned short a,b;if(AmiCopperParseLine(source,&a,&b)){fprintf(stderr,"invalid source accepted: %s\n",source);return 0;}return 1;}
int main(void){const char *invalid[]={"MOVE COLOR32,$0000","MOVE COLOR0X,$0000","MOVE COLOR00,$10000","MOVE $081,$0000","WAIT 44,1","WAIT 44,0,128","WAIT 44,0,127,255","WAIT 44,0,127,254,2","WAIT 256,0","END extra",0};const char *cases[]={"MOVE COLOR00,$000f","MOVE 0x180,0x0abc","WAIT 44,0","WAIT 44,2","WAIT 100,40,63,126,0","SKIP 120,80,85,170,1","END",0};int i;for(i=0;cases[i];i++)if(!check(cases[i]))return 1;for(i=0;invalid[i];i++)if(!reject(invalid[i]))return 1;puts("AmiCopper parser/formatter round-trip PASS");return 0;}
