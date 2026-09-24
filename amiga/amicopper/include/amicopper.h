#ifndef AMISCENE_AMICOPPER_H
#define AMISCENE_AMICOPPER_H

#define AMICOPPER_NAME "AmiCopper"
#define AMICOPPER_AREXX_PORT "AMICOPPER"
#define AMICOPPER_API_VERSION 1\n#define AMICOPPER_MAX_INSTRUCTIONS 256

struct AmiCopperDocument {
    const char *path;
    unsigned long instruction_count;
    int dirty;
    int valid;\n    unsigned short words[AMICOPPER_MAX_INSTRUCTIONS][2];\n    unsigned long selected;
};

void AmiCopperDocumentInit(struct AmiCopperDocument *doc);
void AmiCopperDocumentMarkDirty(struct AmiCopperDocument *doc);
void AmiCopperDocumentValidated(struct AmiCopperDocument *doc, int valid);
int AmiCopperDocumentInsert(struct AmiCopperDocument *doc, unsigned short w0, unsigned short w1);
int AmiCopperDocumentDelete(struct AmiCopperDocument *doc);
int AmiCopperDocumentValidate(struct AmiCopperDocument *doc, unsigned long *bad_index);
int AmiCopperParseLine(const char *line, unsigned short *w0, unsigned short *w1);
int AmiCopperDocumentInsertSource(struct AmiCopperDocument *doc, const char *line);
int AmiCopperDocumentReplaceSource(struct AmiCopperDocument *doc, const char *line);

#endif
