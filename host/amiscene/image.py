"""Image asset pipeline helpers.

PNG decoding is optional and uses Pillow on the host. Core planar conversion
remains dependency-free.
"""
from .bitplane import chunky_to_planar,interleave,emit_incbin

def rgb4(rgb):
    return tuple(max(0,min(15,round(v*15/255))) for v in rgb)

def amiga_color_word(rgb):
    r,g,b=rgb4(rgb)
    return (r<<8)|(g<<4)|b

def emit_palette_asm(palette,label="palette",per_line=8):
    words=[amiga_color_word(c) for c in palette]
    lines=["    cnop 0,2",label+":"]
    for i in range(0,len(words),per_line):
        lines.append("    dc.w "+",".join("$%03x" % w for w in words[i:i+per_line]))
    lines += [label+"_end:",label+"_count equ ("+label+"_end-"+label+")/2"]
    return "\n".join(lines)+"\n"

def load_png(path,planes):
    try:
        from PIL import Image
    except ImportError as exc:
        raise RuntimeError("PNG input requires Pillow on the host") from exc
    limit=1<<planes
    image=Image.open(path).convert("RGB")
    if image.width%8: raise ValueError("PNG width must be divisible by 8")
    q=image.quantize(colors=limit)
    palette_raw=q.getpalette()[:limit*3]
    palette=[tuple(palette_raw[i:i+3]) for i in range(0,len(palette_raw),3)]
    pixels=list(q.getdata())
    return image.width,image.height,pixels,palette

def build_png(path,planes,layout="interleaved"):
    width,height,pixels,palette=load_png(path,planes)
    ps=chunky_to_planar(pixels,width,height,planes)
    if layout=="interleaved": data=interleave(ps)
    elif layout=="separate": data=b"".join(ps)
    else: raise ValueError("layout must be interleaved or separate")
    return {"width":width,"height":height,"planes":planes,"palette":palette,"data":data}
