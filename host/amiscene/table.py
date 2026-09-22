"""ASM-oriented lookup-table generators."""
import math
def sine(entries=256,amplitude=32767):
    if entries<=0: raise ValueError("entries must be positive")
    return [round(math.sin(2*math.pi*i/entries)*amplitude) for i in range(entries)]
def cosine(entries=256,amplitude=32767):
    if entries<=0: raise ValueError("entries must be positive")
    return [round(math.cos(2*math.pi*i/entries)*amplitude) for i in range(entries)]
def emit_asm(values,label="table",directive="dc.w",per_line=8,align=2):
    if directive not in ("dc.b","dc.w","dc.l"): raise ValueError("bad directive")
    lines=[]
    if align: lines.append("    cnop 0,%d" % align)
    lines.append(label+":")
    for i in range(0,len(values),per_line): lines.append("    "+directive+" "+",".join(str(v) for v in values[i:i+per_line]))
    lines += [label+"_end:",label+"_size equ "+label+"_end-"+label]
    return "\n".join(lines)+"\n"
