#include "amicopper.h"

void AmiCopperDocumentInit(struct AmiCopperDocument *doc)
{
    doc->path = 0;
    doc->instruction_count = 0;
    doc->dirty = 0;
    doc->valid = 0;
}

void AmiCopperDocumentMarkDirty(struct AmiCopperDocument *doc)
{
    doc->dirty = 1;
    doc->valid = 0;
}

void AmiCopperDocumentValidated(struct AmiCopperDocument *doc, int valid)
{
    doc->valid = valid ? 1 : 0;
}
