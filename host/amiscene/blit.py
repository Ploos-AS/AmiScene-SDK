"""AmiBlit: explicit OCS Blitter descriptor validation and ASM generation."""
MINTERMS={"copy_a":0xF0,"copy_b":0xCC,"copy_c":0xAA,"cookie_cut":0xCA}
CHANNEL_BITS={"a":0x0800,"b":0x0400,"c":0x0200,"d":0x0100}
BLTCON1_FLAGS={"exclusive_fill":0x0010,"inclusive_fill":0x0008,"fill_carry":0x0004,"descending":0x0002,"line":0x0001}
def descriptor(**kw):
 d={"channels":"ad","minterm":MINTERMS["copy_a"],"ashift":0,"bshift":0,"afwm":0xffff,"alwm":0xffff,
    "amod":0,"bmod":0,"cmod":0,"dmod":0,"width":1,"height":1,"flags":0}
 d.update(kw);validate(d);return d
def validate(d):
 channels=str(d["channels"]).lower()
 if not channels or any(c not in "abcd" for c in channels) or len(set(channels))!=len(channels):raise ValueError("channels must be unique letters from abcd")
 if not 0<=int(d["minterm"])<=255:raise ValueError("minterm must be 0..255")
 for n in ("ashift","bshift"):
  if not 0<=int(d[n])<=15:raise ValueError(n+" must be 0..15")
 for n in ("afwm","alwm"):
  if not 0<=int(d[n])<=0xffff:raise ValueError(n+" must be 0..65535")
 for n in ("amod","bmod","cmod","dmod"):
  if not -32768<=int(d[n])<=32767:raise ValueError(n+" must fit signed word")
 if not 1<=int(d["width"])<=64:raise ValueError("width must be 1..64 words")
 if not 1<=int(d["height"])<=1024:raise ValueError("height must be 1..1024 lines")
 return d
def bltcon0(d):
 return (int(d["ashift"])<<12)|sum(CHANNEL_BITS[c] for c in str(d["channels"]).lower())|int(d["minterm"])
def bltcon1(d):return int(d["bshift"])<<12|int(d.get("flags",0))
LINE_OCTANT_BITS={0:0x18,1:0x04,2:0x0c,3:0x1c,4:0x14,5:0x08,6:0x00,7:0x10}
def line_descriptor(x1,y1,x2,y2,bitplane_bytes,texture=0xffff,texture_start=0,one_dot=False,minterm=0x4a):
 dx0=abs(int(x2)-int(x1));dy0=abs(int(y2)-int(y1))
 dx=max(dx0,dy0);dy=min(dx0,dy0)
 if dx>1023:raise ValueError("line length must be <= 1024 pixels")
 if not 0<=int(texture_start)<=15:raise ValueError("texture_start must be 0..15")
 sx=1 if x2>=x1 else -1;sy=1 if y2>=y1 else -1
 if sx>=0 and sy>=0:octant=0 if dx0>=dy0 else 1
 elif sx<0 and sy>=0:octant=2 if dx0<dy0 else 3
 elif sx<0 and sy<0:octant=4 if dx0>=dy0 else 5
 else:octant=6 if dx0<dy0 else 7
 err=4*dy-2*dx
 flags=BLTCON1_FLAGS["line"]|LINE_OCTANT_BITS[octant]|(0x40 if err<0 else 0)|(0x02 if one_dot else 0)
 return {"mode":"line","bltcon0":((int(x1)&15)<<12)|0x0b00|int(minterm),"bltcon1":(int(texture_start)<<12)|flags,
         "afwm":0xffff,"alwm":0xffff,"amod":4*(dy-dx),"bmod":4*dy,"cmod":int(bitplane_bytes),"dmod":int(bitplane_bytes),
         "apt":err,"adat":0x8000,"bdat":int(texture)&0xffff,"width":2,"height":dx+1,"octant":octant}

def fill_descriptor(mode="inclusive",carry=False,**kw):
 if mode not in ("inclusive","exclusive"):raise ValueError("fill mode must be inclusive or exclusive")
 flags=BLTCON1_FLAGS[mode+"_fill"]|BLTCON1_FLAGS["descending"]
 if carry:flags|=BLTCON1_FLAGS["fill_carry"]
 if "flags" in kw:flags|=int(kw.pop("flags"))
 return descriptor(flags=flags,**kw)
def bltsize(d):return ((int(d["height"])&0x3ff)<<6)|(int(d["width"])&0x3f)
def emit_asm(d,label="BlitDesc"):
 validate(d)
 vals=[bltcon0(d),bltcon1(d),int(d["afwm"]),int(d["alwm"]),int(d["amod"])&0xffff,int(d["bmod"])&0xffff,int(d["cmod"])&0xffff,int(d["dmod"])&0xffff,bltsize(d)]
 names=["BLTCON0","BLTCON1","BLTAFWM","BLTALWM","BLTAMOD","BLTBMOD","BLTCMOD","BLTDMOD","BLTSIZE"]
 lines=[label+":"]+["    dc.w $%04x    ; %s"%(v,n) for v,n in zip(vals,names)]
 lines += [label+"_end:",label+"_size equ "+label+"_end-"+label]
 return "\n".join(lines)+"\n"

def number(s):
 if isinstance(s,int):return s
 return int(s[1:],16) if s.startswith("$") else int(s,0)
def parse(text):
 d={}
 for lineno,raw in enumerate(text.splitlines(),1):
  line=raw.split(";",1)[0].strip()
  if not line:continue
  parts=line.split(None,1)
  if len(parts)!=2:raise ValueError("line %d: expected key value"%lineno)
  key,value=parts[0].lower(),parts[1].strip()
  if key=="channels":d[key]=value.lower()
  elif key=="fill":
   mode=value.lower()
   if mode not in ("inclusive","exclusive"):raise ValueError("line %d: fill must be inclusive or exclusive"%lineno)
   d["flags"]=int(d.get("flags",0))|BLTCON1_FLAGS[mode+"_fill"]|BLTCON1_FLAGS["descending"]
  elif key=="fill_carry":
   if value.lower() not in ("0","1","false","true","no","yes"):raise ValueError("line %d: fill_carry must be boolean"%lineno)
   if value.lower() in ("1","true","yes"):d["flags"]=int(d.get("flags",0))|BLTCON1_FLAGS["fill_carry"]
  elif key=="minterm":d[key]=MINTERMS[value.lower()] if value.lower() in MINTERMS else number(value)
  elif key in ("ashift","bshift","afwm","alwm","amod","bmod","cmod","dmod","width","height","flags"):d[key]=number(value)
  else:raise ValueError("line %d: unknown AmiBlit field %s"%(lineno,key))
 return descriptor(**d)
