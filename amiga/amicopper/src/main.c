#include <stdio.h>
#include "amicopper.h"

int main(void)
{
    struct AmiCopperDocument doc;
    AmiCopperDocumentInit(&doc);

    puts(AMICOPPER_NAME " native M0");
    puts("ARexx port contract: " AMICOPPER_AREXX_PORT);
    puts("GUI/ARexx implementation follows; runtime remains OS-independent.");
    return doc.dirty;
}
