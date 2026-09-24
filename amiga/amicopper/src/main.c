#include <stdio.h>
#include "amicopper.h"
#include "amicopper_ui.h"

int main(void)
{
    struct AmiCopperDocument doc;
    struct AmiCopperUI ui;
    AmiCopperDocumentInit(&doc);
    doc.words[0][0]=0x2c01; doc.words[0][1]=0xfffe;
    doc.words[1][0]=0x0180; doc.words[1][1]=0x0003;
    doc.words[2][0]=0x5001; doc.words[2][1]=0xfffe;
    doc.words[3][0]=0x0180; doc.words[3][1]=0x0006;
    doc.words[4][0]=0xffff; doc.words[4][1]=0xfffe;
    doc.instruction_count=5;
    ui.document=&doc;

    if (!AmiCopperUIOpen(&ui)) {
        fputs("AmiCopper: unable to open Intuition window\n", stderr);
        return 20;
    }

    AmiCopperUIRun(&ui);
    AmiCopperUIClose(&ui);
    return 0;
}
