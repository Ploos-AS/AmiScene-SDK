#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "amicopper.h"

static int num(const char *s, unsigned long *v){ char *e; int base=10; if(*s=='$'){s++;base=16;} *v=strtoul(s,&e,base); return e!=s && *e==0; }
static int reg(const char *s,unsigned long *v){ int n; if(!strncmp(s,"COLOR",5)){ n=atoi(s+5); if(n>=0&&n<32){*v=0x180+n*2;return 1;} } return num(s,v)&&*v>=0x80&&*v<=0x1fe&&!(*v&1); }
int AmiCopperParseLine(const char *line,unsigned short *w0,unsigned short *w1)
{
 char b[96],*op,*a,*c; unsigned long x,y; size_t i;
 for(i=0;i<sizeof(b)-1&&line[i]&&line[i]!=';';i++) b[i]=(line[i]==',')?' ':line[i]; b[i]=0;
 op=strtok(b," \t\r\n"); if(!op)return 0; for(i=0;op[i];i++)op[i]=(char)toupper((unsigned char)op[i]);
 if(!strcmp(op,"END")){*w0=0xffff;*w1=0xfffe;return strtok(0," \t\r\n")==0;}
 a=strtok(0," \t\r\n"); c=strtok(0," \t\r\n"); if(!a||!c)return 0;
 if(!strcmp(op,"MOVE")){ if(!reg(a,&x)||!num(c,&y)||strtok(0," \t\r\n"))return 0; *w0=(unsigned short)x;*w1=(unsigned short)y;return 1; }
 if(!strcmp(op,"WAIT")||!strcmp(op,"SKIP")){ if(!num(a,&x)||!num(c,&y)||x>255||y>254||(y&1))return 0; *w0=(unsigned short)((x<<8)|y|1);*w1=(unsigned short)(0xfffe|(!strcmp(op,"SKIP")?1:0));return 1; }
 return 0;
}
