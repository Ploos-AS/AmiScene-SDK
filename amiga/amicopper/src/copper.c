#include "amicopper_copper.h"

const char *AmiCopperOpcodeName(enum AmiCopperOpcode opcode)
{
    switch (opcode) {
    case AMICOPPER_MOVE: return "MOVE";
    case AMICOPPER_WAIT: return "WAIT";
    case AMICOPPER_SKIP: return "SKIP";
    case AMICOPPER_END:  return "END";
    }
    return "?";
}

int AmiCopperDecode(unsigned short w0, unsigned short w1, struct AmiCopperInstruction *out)
{
    if (!out) return 0;
    out->word0 = w0; out->word1 = w1;
    if (w0 == 0xffff && w1 == 0xfffe) out->opcode = AMICOPPER_END;
    else if (!(w0 & 1)) out->opcode = AMICOPPER_MOVE;
    else if (w1 & 1) out->opcode = AMICOPPER_SKIP;
    else out->opcode = AMICOPPER_WAIT;
    return 1;
}
