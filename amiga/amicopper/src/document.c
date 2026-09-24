#include "amicopper.h"

void AmiCopperDocumentInit(struct AmiCopperDocument *doc)
{
    doc->path = 0;
    doc->instruction_count = 0;
    doc->dirty = 0;
    doc->valid = 0;
    doc->selected = 0;
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
    int ended=0, have_wait=0;
    unsigned short last_v=0, last_h=0;
    for(i=0;i<doc->instruction_count;i++) {
        unsigned short a=doc->words[i][0], b=doc->words[i][1];
        if(ended) goto bad;
        if(a==0xffff && b==0xfffe) { ended=1; continue; }
        if(!(a&1)) {
            /* Copper MOVE destination is an even custom-register offset. */
            if(a < 0x0080 || a > 0x01fe) goto bad;
        } else {
            unsigned short v=(a>>8)&0xff, h=a&0xfe;
            /* WAIT/SKIP IR2 low bit distinguishes SKIP; compare masks use even H bits. */
            if((b&0x00fe)>0x00fe) goto bad;
            if(!(b&1)) {
                if(have_wait && (v<last_v || (v==last_v && h<last_h))) goto bad;
                last_v=v; last_h=h; have_wait=1;
            }
        }
    }
    if(!ended) goto bad_end;
    AmiCopperDocumentValidated(doc,1); return 1;
bad:
    if(bad_index)*bad_index=i; AmiCopperDocumentValidated(doc,0); return 0;
bad_end:
    if(bad_index)*bad_index=doc->instruction_count; AmiCopperDocumentValidated(doc,0); return 0;
}

int AmiCopperDocumentInsertSource(struct AmiCopperDocument *doc, const char *line)
{
    unsigned short w0,w1;
    if(!AmiCopperParseLine(line,&w0,&w1)) return 0;
    return AmiCopperDocumentInsert(doc,w0,w1);
}

int AmiCopperDocumentReplaceSource(struct AmiCopperDocument *doc, const char *line)
{
    unsigned short w0,w1;
    if(!doc->instruction_count || !AmiCopperParseLine(line,&w0,&w1)) return 0;
    doc->words[doc->selected][0]=w0;
    doc->words[doc->selected][1]=w1;
    AmiCopperDocumentMarkDirty(doc);
    return 1;
}
