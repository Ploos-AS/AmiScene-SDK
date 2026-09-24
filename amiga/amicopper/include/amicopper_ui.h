#ifndef AMISCENE_AMICOPPER_UI_H
#define AMISCENE_AMICOPPER_UI_H
#include "amicopper_copper.h"
struct AmiCopperUI { void *window; int running; struct AmiCopperInstruction selected; };
int AmiCopperUIOpen(struct AmiCopperUI *ui);
void AmiCopperUIClose(struct AmiCopperUI *ui);
void AmiCopperUIRun(struct AmiCopperUI *ui);
#endif
