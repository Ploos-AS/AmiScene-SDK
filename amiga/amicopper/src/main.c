#include <stdio.h>
#include "amicopper.h"
#include "amicopper_ui.h"

int main(void)
{
    struct AmiCopperDocument doc;
    struct AmiCopperUI ui;
    AmiCopperDocumentInit(&doc);

    if (!AmiCopperUIOpen(&ui)) {
        fputs("AmiCopper: unable to open Intuition window\n", stderr);
        return 20;
    }

    AmiCopperUIRun(&ui);
    AmiCopperUIClose(&ui);
    return 0;
}
