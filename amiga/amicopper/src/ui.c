/* AmiCopper native Intuition shell. */
#include <exec/types.h>
#include <intuition/intuition.h>
#include <devices/inputevent.h>
#include <libraries/gadtools.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include <proto/keymap.h>
#include <proto/gadtools.h>
#include <stdio.h>
#include <string.h>
#include "amicopper_ui.h"

static void draw_shell(struct Window *w, struct AmiCopperUI *ui)
{
 struct RastPort *rp=w->RPort; unsigned long i; char line[96];
 Move(rp,12,34); Text(rp,(STRPTR)"Copper list / source",20); Move(rp,330,34); Text(rp,(STRPTR)"Inspector",9);
 for(i=0;i<ui->document->instruction_count&&i<8;i++){struct AmiCopperInstruction x;AmiCopperDecode(ui->document->words[i][0],ui->document->words[i][1],&x);sprintf(line,"%c %02lu %-4s $%04x,$%04x",(i==ui->document->selected)?'>':' ',i,AmiCopperOpcodeName(x.opcode),x.word0,x.word1);Move(rp,12,50+i*14);Text(rp,(STRPTR)line,(LONG)strlen(line));}
 sprintf(line,"%s  $%04x,$%04x",AmiCopperOpcodeName(ui->selected.opcode),ui->selected.word0,ui->selected.word1);Move(rp,330,50);Text(rp,(STRPTR)line,(LONG)strlen(line));
 if(ui->editing){Move(rp,12,174);Text(rp,(STRPTR)"> ",2);Text(rp,(STRPTR)ui->edit,(LONG)ui->edit_len);}
 sprintf(line,"M0 %s/%s | O open Ctrl-S save Tab edit F5 validate",ui->document->dirty?"DIRTY":"CLEAN",ui->document->valid?"VALID":"UNVALIDATED");Move(rp,12,190);Text(rp,(STRPTR)line,(LONG)strlen(line));
}
static void refresh_selected(struct AmiCopperUI *ui){
 if(ui->document->instruction_count){if(ui->document->selected>=ui->document->instruction_count)ui->document->selected=ui->document->instruction_count-1;AmiCopperDecode(ui->document->words[ui->document->selected][0],ui->document->words[ui->document->selected][1],&ui->selected);}
 else{ui->document->selected=0;memset(&ui->selected,0,sizeof(ui->selected));}
}
static void append_rawkey(struct AmiCopperUI *ui,UWORD code,UWORD qualifier){struct InputEvent ie;char out[8];LONG n;memset(&ie,0,sizeof(ie));ie.ie_Class=IECLASS_RAWKEY;ie.ie_Code=code;ie.ie_Qualifier=qualifier;n=MapRawKey(&ie,out,sizeof(out),0);if(n==1&&out[0]>=32&&out[0]<127&&ui->edit_len+1<sizeof(ui->edit)){ui->edit[ui->edit_len++]=out[0];ui->edit[ui->edit_len]=0;}}
int AmiCopperUIOpen(struct AmiCopperUI *ui){struct Window*w;ui->window=0;ui->running=0;w=OpenWindowTags(0,WA_Title,(ULONG)"AmiCopper",WA_Left,16,WA_Top,16,WA_Width,620,WA_Height,220,WA_DragBar,TRUE,WA_DepthGadget,TRUE,WA_CloseGadget,TRUE,WA_Activate,TRUE,WA_IDCMP,IDCMP_CLOSEWINDOW|IDCMP_RAWKEY|IDCMP_REFRESHWINDOW,TAG_DONE);if(!w)return 0;ui->window=w;ui->running=1;ui->editing=0;ui->edit_len=0;ui->edit[0]=0;strcpy(ui->path,"amicopper.copper");ui->arexx_port=AmiCopperRexxOpen();if(!ui->arexx_port){CloseWindow(w);ui->window=0;ui->running=0;return 0;}return 1;}
void AmiCopperUIClose(struct AmiCopperUI *ui){if(ui->arexx_port)AmiCopperRexxClose((struct MsgPort*)ui->arexx_port);ui->arexx_port=0;if(ui->window)CloseWindow((struct Window*)ui->window);ui->window=0;ui->running=0;}
void AmiCopperUIRun(struct AmiCopperUI *ui){struct Window*w=(struct Window*)ui->window;refresh_selected(ui);draw_shell(w,ui);while(ui->running){struct IntuiMessage*msg;ULONG ws=(1UL<<w->UserPort->mp_SigBit)|(1UL<<((struct MsgPort*)ui->arexx_port)->mp_SigBit);ULONG got=Wait(ws);if(got&(1UL<<((struct MsgPort*)ui->arexx_port)->mp_SigBit)){int q=0;AmiCopperRexxDrain((struct MsgPort*)ui->arexx_port,ui->document,&q);if(q){ui->running=0;continue;}refresh_selected(ui);draw_shell(w,ui);}while((msg=(struct IntuiMessage*)GetMsg(w->UserPort))){ULONG cls=msg->Class;UWORD code=msg->Code,qual=msg->Qualifier;ReplyMsg((struct Message*)msg);if(cls==IDCMP_REFRESHWINDOW){BeginRefresh(w);draw_shell(w,ui);EndRefresh(w,TRUE);continue;}if(cls==IDCMP_CLOSEWINDOW){ui->running=0;continue;}if(cls!=IDCMP_RAWKEY)continue;
 if(ui->editing){if(code==0x44){if(AmiCopperDocumentReplaceSource(ui->document,ui->edit)){ui->editing=0;refresh_selected(ui);}}else if(code==0x41&&ui->edit_len)ui->edit[--ui->edit_len]=0;else if(code==0x45)ui->editing=0;else if(!(code&0x80))append_rawkey(ui,code,qual);draw_shell(w,ui);continue;}
 if(code==0x4c&&ui->document->selected)ui->document->selected--;else if(code==0x4d&&ui->document->selected+1<ui->document->instruction_count)ui->document->selected++;else if(code==0x37)AmiCopperDocumentInsert(ui->document,0x0180,0);else if(code==0x11)AmiCopperDocumentInsert(ui->document,0x2c01,0xfffe);else if(code==0x21&&(qual&(IEQUALIFIER_CONTROL|IEQUALIFIER_LCOMMAND|IEQUALIFIER_RCOMMAND))){AmiCopperDocumentSave(ui->document,ui->path);}else if(code==0x21)AmiCopperDocumentInsert(ui->document,0x2c01,0xffff);else if(code==0x46)AmiCopperDocumentDelete(ui->document);else if(code==0x50){unsigned long bad=0;if(!AmiCopperDocumentValidate(ui->document,&bad)&&bad<ui->document->instruction_count)ui->document->selected=bad;}else if(code==0x18){if(AmiCopperDocumentLoad(ui->document,ui->path))refresh_selected(ui);}else if(code==0x42){ui->editing=1;AmiCopperFormatSource(&ui->selected,ui->edit,sizeof(ui->edit));ui->edit_len=(unsigned int)strlen(ui->edit);}else if(code==0x45)ui->running=0;refresh_selected(ui);draw_shell(w,ui);
 }}}
