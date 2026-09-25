#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "amicopper.h"

static int num(const char *s, unsigned long *v){ char *e; int base=10; if(!s||!*s)return 0; if(*s=='
struct RegName { const char *name; unsigned short offset; };
static const struct RegName regs[]={
 {"DIWSTRT",0x08e},{"DIWSTOP",0x090},{"DDFSTRT",0x092},{"DDFSTOP",0x094},{"DMACON",0x096},{"INTENA",0x09a},{"INTREQ",0x09c},{"ADKCON",0x09e},
 {"BPLCON0",0x100},{"BPLCON1",0x102},{"BPLCON2",0x104},{"BPL1MOD",0x108},{"BPL2MOD",0x10a}
};
static int reg(const char *s,unsigned long *v){ int n,i; char u[24]; size_t j; for(j=0;j<sizeof(u)-1&&s[j];j++)u[j]=(char)toupper((unsigned char)s[j]);u[j]=0;
 for(i=0;i<(int)(sizeof(regs)/sizeof(regs[0]));i++)if(!strcmp(u,regs[i].name)){*v=regs[i].offset;return 1;}
 if(!strncmp(u,"COLOR",5)){const char *p=u+5;if(!*p)return 0;for(j=0;p[j];j++)if(!isdigit((unsigned char)p[j]))return 0;n=atoi(p);if(n>=0&&n<32){*v=0x180+n*2;return 1;}return 0;}
 if(!strncmp(u,"BPL",3)&&u[3]>='1'&&u[3]<='6'&&(!strcmp(u+4,"PTH")||!strcmp(u+4,"PTL"))){n=u[3]-'1';*v=0x0e0+n*4+(!strcmp(u+4,"PTL")?2:0);return 1;}
 if(!strncmp(u,"SPR",3)&&u[3]>='0'&&u[3]<='7'){n=u[3]-'0';if(!strcmp(u+4,"PTH")||!strcmp(u+4,"PTL")){*v=0x120+n*4+(!strcmp(u+4,"PTL")?2:0);return 1;}if(!strcmp(u+4,"POS")||!strcmp(u+4,"CTL")){*v=0x140+n*8+(!strcmp(u+4,"CTL")?2:0);return 1;}}
 return num(s,v)&&*v>=0x80&&*v<=0x1fe&&!(*v&1); }
int AmiCopperParseLine(const char *line,unsigned short *w0,unsigned short *w1)
{
 char b[96],*op,*a,*c,*d,*e,*f; unsigned long x,y,vm,hm,bfd; size_t i;
 for(i=0;i<sizeof(b)-1&&line[i]&&line[i]!=';';i++) b[i]=(line[i]==',')?' ':line[i]; b[i]=0;
 op=strtok(b," \t\r\n"); if(!op)return 0; for(i=0;op[i];i++)op[i]=(char)toupper((unsigned char)op[i]);
 if(!strcmp(op,"END")){*w0=0xffff;*w1=0xfffe;return strtok(0," \t\r\n")==0;}
 a=strtok(0," \t\r\n"); c=strtok(0," \t\r\n"); if(!a||!c)return 0;
 if(!strcmp(op,"MOVE")){ if(!reg(a,&x)||!num(c,&y)||strtok(0," \t\r\n"))return 0; *w0=(unsigned short)x;*w1=(unsigned short)y;return 1; }
 if(!strcmp(op,"WAIT")||!strcmp(op,"SKIP")){ d=strtok(0," \t\r\n"); e=strtok(0," \t\r\n"); f=strtok(0," \t\r\n"); if(strtok(0," \t\r\n"))return 0; vm=0x7f;hm=0xfe;bfd=1; if(!num(a,&x)||!num(c,&y)||x>255||y>254||(y&1))return 0; if(d&&(!num(d,&vm)||vm>0x7f))return 0; if(e&&(!num(e,&hm)||hm>0xfe||(hm&1)))return 0; if(f&&(!num(f,&bfd)||bfd>1))return 0; *w0=(unsigned short)((x<<8)|y|1);*w1=(unsigned short)((bfd?0x8000:0)|(vm<<8)|hm|(!strcmp(op,"SKIP")?1:0));return 1; }
 return 0;
}
){s++;base=16;if(!*s)return 0;} else if(s[0]=='0'&&(s[1]=='x'||s[1]=='X'))base=0; *v=strtoul(s,&e,base); return e!=s && *e==0; }
struct RegName { const char *name; unsigned short offset; };
static const struct RegName regs[]={
 {"DIWSTRT",0x08e},{"DIWSTOP",0x090},{"DDFSTRT",0x092},{"DDFSTOP",0x094},{"DMACON",0x096},{"INTENA",0x09a},{"INTREQ",0x09c},{"ADKCON",0x09e},
 {"BPLCON0",0x100},{"BPLCON1",0x102},{"BPLCON2",0x104},{"BPL1MOD",0x108},{"BPL2MOD",0x10a}
};
static int reg(const char *s,unsigned long *v){ int n,i; char u[24]; size_t j; for(j=0;j<sizeof(u)-1&&s[j];j++)u[j]=(char)toupper((unsigned char)s[j]);u[j]=0;
 for(i=0;i<(int)(sizeof(regs)/sizeof(regs[0]));i++)if(!strcmp(u,regs[i].name)){*v=regs[i].offset;return 1;}
 if(!strncmp(u,"COLOR",5)){n=atoi(u+5);if(n>=0&&n<32){*v=0x180+n*2;return 1;}}
 if(!strncmp(u,"BPL",3)&&u[3]>='1'&&u[3]<='6'&&(!strcmp(u+4,"PTH")||!strcmp(u+4,"PTL"))){n=u[3]-'1';*v=0x0e0+n*4+(!strcmp(u+4,"PTL")?2:0);return 1;}
 if(!strncmp(u,"SPR",3)&&u[3]>='0'&&u[3]<='7'){n=u[3]-'0';if(!strcmp(u+4,"PTH")||!strcmp(u+4,"PTL")){*v=0x120+n*4+(!strcmp(u+4,"PTL")?2:0);return 1;}if(!strcmp(u+4,"POS")||!strcmp(u+4,"CTL")){*v=0x140+n*8+(!strcmp(u+4,"CTL")?2:0);return 1;}}
 return num(s,v)&&*v>=0x80&&*v<=0x1fe&&!(*v&1); }
int AmiCopperParseLine(const char *line,unsigned short *w0,unsigned short *w1)
{
 char b[96],*op,*a,*c,*d,*e,*f; unsigned long x,y,vm,hm,bfd; size_t i;
 for(i=0;i<sizeof(b)-1&&line[i]&&line[i]!=';';i++) b[i]=(line[i]==',')?' ':line[i]; b[i]=0;
 op=strtok(b," \t\r\n"); if(!op)return 0; for(i=0;op[i];i++)op[i]=(char)toupper((unsigned char)op[i]);
 if(!strcmp(op,"END")){*w0=0xffff;*w1=0xfffe;return strtok(0," \t\r\n")==0;}
 a=strtok(0," \t\r\n"); c=strtok(0," \t\r\n"); if(!a||!c)return 0;
 if(!strcmp(op,"MOVE")){ if(!reg(a,&x)||!num(c,&y)||strtok(0," \t\r\n"))return 0; *w0=(unsigned short)x;*w1=(unsigned short)y;return 1; }
 if(!strcmp(op,"WAIT")||!strcmp(op,"SKIP")){ d=strtok(0," \t\r\n"); e=strtok(0," \t\r\n"); f=strtok(0," \t\r\n"); if(strtok(0," \t\r\n"))return 0; vm=0x7f;hm=0xfe;bfd=1; if(!num(a,&x)||!num(c,&y)||x>255||y>254||(y&1))return 0; if(d&&(!num(d,&vm)||vm>0x7f))return 0; if(e&&(!num(e,&hm)||hm>0xfe||(hm&1)))return 0; if(f&&(!num(f,&bfd)||bfd>1))return 0; *w0=(unsigned short)((x<<8)|y|1);*w1=(unsigned short)((bfd?0x8000:0)|(vm<<8)|hm|(!strcmp(op,"SKIP")?1:0));return 1; }
 return 0;
}
