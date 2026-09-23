"""AmiCopper: readable OCS Copper authoring, validation and ASM generation."""
OCS_REGISTERS={"DIWSTRT":0x08e,"DIWSTOP":0x090,"DDFSTRT":0x092,"DDFSTOP":0x094,"DMACON":0x096,"INTENA":0x09a,"INTREQ":0x09c,"ADKCON":0x09e,"BPLCON0":0x100,"BPLCON1":0x102,"BPLCON2":0x104,"BPL1MOD":0x108,"BPL2MOD":0x10a}
for i in range(1,7):OCS_REGISTERS["BPL%dPTH"%i]=0x0e0+(i-1)*4;OCS_REGISTERS["BPL%dPTL"%i]=0x0e2+(i-1)*4
for i in range(8):OCS_REGISTERS["SPR%dPTH"%i]=0x120+i*4;OCS_REGISTERS["SPR%dPTL"%i]=0x122+i*4;OCS_REGISTERS["SPR%dPOS"%i]=0x140+i*8;OCS_REGISTERS["SPR%dCTL"%i]=0x142+i*8
OCS_REGISTERS.update({"COLOR%02d"%i:0x180+i*2 for i in range(32)})
DANGEROUS={"DMACON":"changes DMA enable state","INTENA":"changes interrupt enable state","INTREQ":"changes interrupt requests","ADKCON":"changes audio/disk control state"}
def number(s):return int(s[1:],16) if s.startswith("$") else int(s,0)
def register(value):
 if isinstance(value,str):
  key=value.upper()
  if key not in OCS_REGISTERS:raise ValueError("unknown OCS register: "+value)
  return OCS_REGISTERS[key]
 value=int(value)
 if value<0x080 or value>0x1fe or value&1:raise ValueError("Copper MOVE register must be even $080..$1fe")
 return value
def move(reg,value):return register(reg),int(value)&0xffff
def wait(v,h=0,vmask=0x7f,hmask=0xfe,bfd=True):
 if not 0<=v<=255 or not 0<=h<=254:raise ValueError("WAIT position out of range")
 if h&1:raise ValueError("Copper horizontal position must be even")
 if not 0<=vmask<=0x7f or not 0<=hmask<=254 or hmask&1:raise ValueError("WAIT mask out of range")
 return (v<<8)|h|1,(0x8000 if bfd else 0)|((vmask&0x7f)<<8)|(hmask&0xfe)
def skip(v,h=0,vmask=0x7f,hmask=0xfe,bfd=True):a,b=wait(v,h,vmask,hmask,bfd);return a,b|1
def end():return 0xffff,0xfffe
def parse(text):
 commands=[]
 for lineno,raw in enumerate(text.splitlines(),1):
  line=raw.split(";",1)[0].strip()
  if not line:continue
  parts=line.replace(","," ").split();op=parts[0].upper()
  try:
   if op=="MOVE" and len(parts)==3:commands.append(("move",(parts[1],number(parts[2]))))
   elif op in ("WAIT","SKIP") and 2<=len(parts)<=5:commands.append((op.lower(),tuple(number(x) for x in parts[1:])))
   elif op=="END" and len(parts)==1:commands.append(("end",()))
   else:raise ValueError("syntax")
  except ValueError as e:raise ValueError("line %d: %s"%(lineno,e)) from e
 return commands
def diagnose(commands):
 errors=[];warnings=[];last=None
 for i,(kind,args) in enumerate(commands,1):
  try:
   if kind in ("wait","skip"):
    wait(*args);v=args[0];h=args[1] if len(args)>1 else 0;pos=(v,h)
    if kind=="wait" and last is not None and pos<last:errors.append("command %d: WAIT moves backwards in raster order"%i)
    if kind=="wait":last=pos
    if len(args)>2 and args[2]!=0x7f:warnings.append("command %d: vertical WAIT mask is non-default; verify intentional masked compare"%i)
    if len(args)>3 and args[3]!=0xfe:warnings.append("command %d: horizontal WAIT mask is non-default; verify intentional masked compare"%i)
   elif kind=="move":
    register(args[0]);name=str(args[0]).upper()
    if name in DANGEROUS:warnings.append("command %d: MOVE %s %s"%(i,name,DANGEROUS[name]))
   elif kind=="end":
    if i!=len(commands):errors.append("command %d: commands after END are unreachable"%i)
   else:errors.append("command %d: unknown command %s"%(i,kind))
  except ValueError as e:errors.append("command %d: %s"%(i,e))
 if not commands or commands[-1][0]!="end":errors.append("Copper list has no END marker")
 return {"errors":errors,"warnings":warnings}
def validate(commands,pal=True):return diagnose(commands)["errors"]
def emit_asm(commands,label="CopperList"):
 d=diagnose(commands)
 if d["errors"]:raise ValueError("; ".join(d["errors"]))
 lines=["    cnop 0,2",label+":"]
 for kind,args in commands:
  words={"move":move,"wait":wait,"skip":skip,"end":end}[kind](*args);comment=kind.upper()+((" "+str(args[0]).upper()) if kind=="move" else "")
  lines.append("    dc.w $%04x,$%04x    ; %s"%(words[0],words[1],comment))
 lines += [label+"_end:",label+"_size equ "+label+"_end-"+label]
 return "\n".join(lines)+"\n"
