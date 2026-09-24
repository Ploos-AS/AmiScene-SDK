/* AmiCopper native Intuition M0 shell.
 * Keep this layer small: document/Copper semantics do not belong in gadgets.
 */
#include <exec/types.h>
#include <intuition/intuition.h>
#include <proto/exec.h>
#include <proto/intuition.h>
#include "amicopper_ui.h"

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
    ui->running = 1;
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
    draw_shell(w);\n    while (ui->running) {
        struct IntuiMessage *msg;
        Wait(1UL << w->UserPort->mp_SigBit);
        while ((msg = (struct IntuiMessage *)GetMsg(w->UserPort)) != 0) {
            ULONG cls = msg->Class;
            UWORD code = msg->Code;
            ReplyMsg((struct Message *)msg);
            if (cls == IDCMP_REFRESHWINDOW) {\n                BeginRefresh(w);\n                draw_shell(w);\n                EndRefresh(w, TRUE);\n            }\n            if (cls == IDCMP_CLOSEWINDOW)
                ui->running = 0;
            /* ESC is an intentional keyboard-first M0 exit path. */
            if (cls == IDCMP_RAWKEY && code == 0x45)
                ui->running = 0;
        }
    }
}
