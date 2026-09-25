#ifndef AMISCENE_AMICOPPER_UI_H
#define AMISCENE_AMICOPPER_UI_H
#include "amicopper_copper.h"\n#include "amicopper.h"
struct AmiCopperUI { void *window; int running; struct AmiCopperInstruction selected; struct AmiCopperDocument *document; char edit[96]; unsigned int edit_len; int editing; char path[256]; };
int AmiCopperUIOpen(struct AmiCopperUI *ui);
void AmiCopperUIClose(struct AmiCopperUI *ui);
void AmiCopperUIRun(struct AmiCopperUI *ui);
#endif
