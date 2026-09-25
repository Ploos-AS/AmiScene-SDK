#include <exec/types.h>
#include <exec/ports.h>
#include <exec/libraries.h>
#include <rexx/storage.h>
#include <proto/exec.h>
#include <proto/rexxsyslib.h>
#include <string.h>
#include "amicopper.h"

struct Library *RexxSysBase = 0;

struct MsgPort *AmiCopperRexxOpen(void)
{
 struct MsgPort *p;
 if(!SysBase || SysBase->LibNode.lib_Version < 36)return 0;
 if(!RexxSysBase){RexxSysBase=OpenLibrary("rexxsyslib.library",0);if(!RexxSysBase)return 0;}
 Forbid();
 if(FindPort((STRPTR)AMICOPPER_AREXX_PORT)){Permit();CloseLibrary(RexxSysBase);RexxSysBase=0;return 0;}
 p=CreateMsgPort();
 if(!p){Permit();CloseLibrary(RexxSysBase);RexxSysBase=0;return 0;}
 p->mp_Node.ln_Name=(char *)AMICOPPER_AREXX_PORT; p->mp_Node.ln_Pri=0; AddPort(p);
 Permit();
 return p;
}
void AmiCopperRexxClose(struct MsgPort *p){struct RexxMsg*m;if(p){RemPort(p);while((m=(struct RexxMsg*)GetMsg(p))){m->rm_Result1=20;m->rm_Result2=0;ReplyMsg((struct Message*)m);}DeleteMsgPort(p);}if(RexxSysBase){CloseLibrary(RexxSysBase);RexxSysBase=0;}}
void AmiCopperRexxDrain(struct MsgPort *p,struct AmiCopperDocument *doc,int *quit)
{
 struct RexxMsg*m;char result[AMICOPPER_AREXX_RESULT_MAX];int q=0,rc;while(p&&(m=(struct RexxMsg*)GetMsg(p))){const char*cmd=(m->rm_Args[0])?(const char*)m->rm_Args[0]:"";rc=AmiCopperRexxCommand(doc,cmd,result,sizeof(result),&q);m->rm_Result1=rc;m->rm_Result2=0;if((m->rm_Action&RXFF_RESULT)&&result[0])m->rm_Result2=(LONG)CreateArgstring(result,(LONG)strlen(result));ReplyMsg((struct Message*)m);if(q&&quit)*quit=1;}
}
