#include "amicopper_copper.h"\n#include <stdio.h>

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

int AmiCopperFormatSource(const struct AmiCopperInstruction *ins, char *buf, unsigned int size)
{
    unsigned int v,h;
    if(!ins||!buf||!size)return 0;
    switch(ins->opcode){
    case AMICOPPER_MOVE: snprintf(buf,size,"MOVE $%03x,$%04x",ins->word0,ins->word1); break;
    case AMICOPPER_WAIT: v=ins->word0>>8; h=ins->word0&0xfe; snprintf(buf,size,"WAIT %u,%u",v,h); break;
    case AMICOPPER_SKIP: v=ins->word0>>8; h=ins->word0&0xfe; snprintf(buf,size,"SKIP %u,%u",v,h); break;
    case AMICOPPER_END: snprintf(buf,size,"END"); break;
    default:return 0;
    }
    return 1;
}
