#ifndef AMISCENE_AMICOPPER_COPPER_H
#define AMISCENE_AMICOPPER_COPPER_H

enum AmiCopperOpcode { AMICOPPER_MOVE, AMICOPPER_WAIT, AMICOPPER_SKIP, AMICOPPER_END };

struct AmiCopperInstruction {
    enum AmiCopperOpcode opcode;
    unsigned short word0;
    unsigned short word1;
};

const char *AmiCopperOpcodeName(enum AmiCopperOpcode opcode);
int AmiCopperDecode(unsigned short word0, unsigned short word1, struct AmiCopperInstruction *out);
int AmiCopperFormatSource(const struct AmiCopperInstruction *ins, char *buf, unsigned int size);

#endif
