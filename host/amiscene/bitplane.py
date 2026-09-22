"""Amiga planar conversion and ASM emission."""
def chunky_to_planar(pixels,width,height,planes):
    if width<=0 or height<=0 or width%8: raise ValueError("width must be positive and divisible by 8")
    if planes<1 or planes>8: raise ValueError("planes must be 1..8")
    if len(pixels)!=width*height: raise ValueError("pixel count does not match dimensions")
    if any(p<0 or p>=(1<<planes) for p in pixels): raise ValueError("pixel index exceeds plane depth")
    rowbytes=width//8; out=[bytearray(rowbytes*height) for _ in range(planes)]
    for y in range(height):
        for x in range(width):
            value=pixels[y*width+x]; mask=1<<(7-(x&7)); pos=y*rowbytes+(x>>3)
            for plane in range(planes):
                if value&(1<<plane): out[plane][pos]|=mask
    return [bytes(p) for p in out]
def interleave(planes):
    if not planes:return b""
    size=len(planes[0])
    if any(len(p)!=size for p in planes):raise ValueError("plane sizes differ")
    return b"".join(p[i:i+1] for i in range(size) for p in planes)
def emit_asm(data,label="bitmap",per_line=16,align=2):
    lines=[]
    if align:lines.append("    cnop 0,%d" % align)
    lines.append(label+":")
    for i in range(0,len(data),per_line):lines.append("    dc.b "+",".join("$%02x" % b for b in data[i:i+per_line]))
    lines += [label+"_end:",label+"_size equ "+label+"_end-"+label]
    return "\n".join(lines)+"\n"
def emit_incbin(path,label="bitmap",align=2):
    prefix=("    cnop 0,%d\n" % align) if align else ""
    return prefix+label+':\n    incbin "'+path+'"\n'+label+"_end:\n"+label+"_size equ "+label+"_end-"+label+"\n"
