#include "amicopper.h"

void AmiCopperDocumentInit(struct AmiCopperDocument *doc)
{
    doc->path = 0;
    doc->instruction_count = 0;
    doc->dirty = 0;
    doc->valid = 0;\n    doc->selected = 0;
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

int AmiCopperDocumentInsert(struct AmiCopperDocument *doc, unsigned short w0, unsigned short w1)
{
    unsigned long i, at;
    if (doc->instruction_count >= AMICOPPER_MAX_INSTRUCTIONS) return 0;
    at = doc->instruction_count ? doc->selected + 1 : 0;
    for (i=doc->instruction_count; i>at; --i) { doc->words[i][0]=doc->words[i-1][0]; doc->words[i][1]=doc->words[i-1][1]; }
    doc->words[at][0]=w0; doc->words[at][1]=w1; doc->instruction_count++; doc->selected=at; AmiCopperDocumentMarkDirty(doc); return 1;
}

int AmiCopperDocumentDelete(struct AmiCopperDocument *doc)
{
    unsigned long i;
    if (!doc->instruction_count) return 0;
    for (i=doc->selected; i+1<doc->instruction_count; ++i) { doc->words[i][0]=doc->words[i+1][0]; doc->words[i][1]=doc->words[i+1][1]; }
    doc->instruction_count--; if (doc->selected && doc->selected>=doc->instruction_count) doc->selected--; AmiCopperDocumentMarkDirty(doc); return 1;
}
