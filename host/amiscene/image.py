"""Deterministic image asset pipeline for ASM workflows."""
from .bitplane import chunky_to_planar,interleave

def rgb4(rgb): return tuple(max(0,min(15,round(v*15/255))) for v in rgb)
def amiga_color_word(rgb):
    r,g,b=rgb4(rgb); return (r<<8)|(g<<4)|b

def emit_palette_asm(palette,label="palette",per_line=8):
    words=[amiga_color_word(c) for c in palette]; lines=["    cnop 0,2",label+":"]
    for i in range(0,len(words),per_line): lines.append("    dc.w "+",".join("$%03x" % w for w in words[i:i+per_line]))
    lines += [label+"_end:",label+"_count equ ("+label+"_end-"+label+")/2"]
    return "\n".join(lines)+"\n"

def parse_palette(path):
    colors=[]
    for n,line in enumerate(open(path,encoding="utf-8"),1):
        s=line.split("#",1)[0].strip()
        if not s: continue
        if s.startswith("$"): word=int(s[1:],16); colors.append((((word>>8)&15)*17,((word>>4)&15)*17,(word&15)*17)); continue
        parts=s.replace(","," ").split()
        if len(parts)!=3: raise ValueError("bad palette line %d" % n)
        vals=tuple(int(x,0) for x in parts)
        if any(v<0 or v>255 for v in vals): raise ValueError("palette RGB out of range")
        colors.append(vals)
    if not colors: raise ValueError("palette is empty")
    return colors

def _palette_image(Image,palette):
    p=Image.new("P",(1,1)); flat=[]
    for c in palette: flat.extend(c)
    flat += [0]*(768-len(flat)); p.putpalette(flat[:768]); return p

def load_png(path,planes,palette=None,dither=False):
    try: from PIL import Image
    except ImportError as exc: raise RuntimeError("PNG input requires Pillow on the host") from exc
    limit=1<<planes
    if palette is not None and len(palette)>limit: raise ValueError("palette has more colors than plane depth permits")
    image=Image.open(path).convert("RGB")
    if image.width%8: raise ValueError("PNG width must be divisible by 8")
    d=Image.Dither.FLOYDSTEINBERG if dither else Image.Dither.NONE
    if palette is None:
        q=image.quantize(colors=limit,method=Image.Quantize.MEDIANCUT,dither=d)
        raw=q.getpalette()[:limit*3]; palette=[tuple(raw[i:i+3]) for i in range(0,len(raw),3)]
    else:
        q=image.quantize(palette=_palette_image(Image,palette),dither=d)
    return image.width,image.height,list(q.getdata()),palette

def build_png(path,planes,layout="interleaved",palette=None,dither=False):
    width,height,pixels,palette=load_png(path,planes,palette,dither); ps=chunky_to_planar(pixels,width,height,planes)
    if layout=="interleaved": data=interleave(ps)
    elif layout=="separate": data=b"".join(ps)
    else: raise ValueError("layout must be interleaved or separate")
    return {"width":width,"height":height,"planes":planes,"palette":palette,"data":data}
