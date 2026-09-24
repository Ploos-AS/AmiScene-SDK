/* AmiCopper native Intuition M0 shell.
 * Keep this layer small: document/Copper semantics do not belong in gadgets.
 */
#include <exec/types.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include "amicopper_ui.h"\n#include <stdio.h>\n#include <string.h>

int AmiCopperUIOpen(struct AmiCopperUI *ui)
{
    struct Window *w;
    ui->window = 0;
    ui->running = 0;

    w = OpenWindowTags(0,
        WA_Title, (ULONG)"AmiCopper",
        WA_Left, 16,
        WA_Top, 16,
        WA_Width, 620,
        WA_Height, 220,
        WA_DragBar, TRUE,
        WA_DepthGadget, TRUE,
        WA_CloseGadget, TRUE,
        WA_Activate, TRUE,
        WA_IDCMP, IDCMP_CLOSEWINDOW | IDCMP_RAWKEY | IDCMP_REFRESHWINDOW,
        TAG_DONE);
    if (!w)
        return 0;

    ui->window = w;
    ui->running = 1;\n    ui->editing=0; ui->edit_len=0; ui->edit[0]=0;
    return 1;
}

void AmiCopperUIClose(struct AmiCopperUI *ui)
{
    if (ui->window)
        CloseWindow((struct Window *)ui->window);
    ui->window = 0;
    ui->running = 0;
}

void AmiCopperUIRun(struct AmiCopperUI *ui)
{
    struct Window *w = (struct Window *)ui->window;
    AmiCopperDecode(0x2c01, 0xfffe, &ui->selected);\n    draw_shell(w, &ui->selected);\n    while (ui->running) {
        struct IntuiMessage *msg;
        Wait(1UL << w->UserPort->mp_SigBit);
        while ((msg = (struct IntuiMessage *)GetMsg(w->UserPort)) != 0) {
            ULONG cls = msg->Class;
            UWORD code = msg->Code;
            ReplyMsg((struct Message *)msg);
            if (cls == IDCMP_REFRESHWINDOW) {\n                BeginRefresh(w);\n                draw_shell(w, ui);\n                EndRefresh(w, TRUE);\n            }\n            if (cls == IDCMP_CLOSEWINDOW)
                ui->running = 0;
            if (cls == IDCMP_RAWKEY && code == 0x4c && ui->document->selected) ui->document->selected--;
            if (cls == IDCMP_RAWKEY && code == 0x4d && ui->document->selected + 1 < ui->document->instruction_count) ui->document->selected++;
            if (cls == IDCMP_RAWKEY && (code == 0x4c || code == 0x4d)) { AmiCopperDecode(ui->document->words[ui->document->selected][0],ui->document->words[ui->document->selected][1],&ui->selected); draw_shell(w,ui); }
            if (cls == IDCMP_RAWKEY && code == 0x37) AmiCopperDocumentInsert(ui->document,0x0180,0x0000); /* M */
            if (cls == IDCMP_RAWKEY && code == 0x11) AmiCopperDocumentInsert(ui->document,0x2c01,0xfffe); /* W */
            if (cls == IDCMP_RAWKEY && code == 0x21) AmiCopperDocumentInsert(ui->document,0x2c01,0xffff); /* S */
            if (cls == IDCMP_RAWKEY && code == 0x46) AmiCopperDocumentDelete(ui->document); /* Del */
            if (cls == IDCMP_RAWKEY && (code == 0x37 || code == 0x11 || code == 0x21 || code == 0x46)) { if(ui->document->instruction_count) AmiCopperDecode(ui->document->words[ui->document->selected][0],ui->document->words[ui->document->selected][1],&ui->selected); draw_shell(w,ui); }
            if (cls == IDCMP_RAWKEY && code == 0x50) { unsigned long bad=0; if(!AmiCopperDocumentValidate(ui->document,&bad) && bad<ui->document->instruction_count) ui->document->selected=bad; if(ui->document->instruction_count) AmiCopperDecode(ui->document->words[ui->document->selected][0],ui->document->words[ui->document->selected][1],&ui->selected); draw_shell(w,ui); } /* F5 */
            if (cls == IDCMP_RAWKEY && code == 0x42) { ui->editing=1; ui->edit_len=0; ui->edit[0]=0; draw_shell(w,ui); } /* Tab: edit source */\n            if (cls == IDCMP_RAWKEY && ui->editing && code == 0x44) { if(AmiCopperDocumentReplaceSource(ui->document,ui->edit)){ ui->editing=0; AmiCopperDecode(ui->document->words[ui->document->selected][0],ui->document->words[ui->document->selected][1],&ui->selected); } draw_shell(w,ui); } /* Return */\n            if (cls == IDCMP_RAWKEY && ui->editing && code == 0x41 && ui->edit_len) { ui->edit[--ui->edit_len]=0; draw_shell(w,ui); } /* Backspace */\n            /* ESC is an intentional keyboard-first M0 exit path. */
            if (cls == IDCMP_RAWKEY && code == 0x45)
                ui->running = 0;
        }
    }
}
