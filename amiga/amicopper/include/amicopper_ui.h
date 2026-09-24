#ifndef AMISCENE_AMICOPPER_UI_H
#define AMISCENE_AMICOPPER_UI_H

struct AmiCopperUI {
    void *window;
    int running;
};

int AmiCopperUIOpen(struct AmiCopperUI *ui);
void AmiCopperUIClose(struct AmiCopperUI *ui);
void AmiCopperUIRun(struct AmiCopperUI *ui);

#endif
