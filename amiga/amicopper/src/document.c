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

int AmiCopperDocumentValidate(struct AmiCopperDocument *doc, unsigned long *bad_index)
{
    unsigned long i;
    int ended=0;
    for(i=0;i<doc->instruction_count;i++) {
        unsigned short a=doc->words[i][0], b=doc->words[i][1];
        if(ended) { if(bad_index)*bad_index=i; AmiCopperDocumentValidated(doc,0); return 0; }
        if(a==0xffff && b==0xfffe) { ended=1; continue; }
        if(!(a&1)) { if(a&1) { if(bad_index)*bad_index=i; AmiCopperDocumentValidated(doc,0); return 0; } }
        else if((a&0x00fe)&1) { if(bad_index)*bad_index=i; AmiCopperDocumentValidated(doc,0); return 0; }
    }
    if(!ended) { if(bad_index)*bad_index=doc->instruction_count; AmiCopperDocumentValidated(doc,0); return 0; }
    AmiCopperDocumentValidated(doc,1); return 1;
}
