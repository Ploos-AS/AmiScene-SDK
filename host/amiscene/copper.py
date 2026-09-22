"""AmiCopper: readable OCS Copper list construction."""
OCS_REGISTERS={"BPLCON0":0x100,"BPLCON1":0x102,"BPLCON2":0x104,"BPL1MOD":0x108,"BPL2MOD":0x10a,"DIWSTRT":0x08e,"DIWSTOP":0x090,"DDFSTRT":0x092,"DDFSTOP":0x094}
OCS_REGISTERS.update({"COLOR%d"%i:0x180+i*2 for i in range(32)})
def register(value):
 if isinstance(value,str):
  key=value.upper()
  if key not in OCS_REGISTERS:raise ValueError("unknown OCS register: "+value)
  return OCS_REGISTERS[key]
 value=int(value)
 if value<0x080 or value>0x1fe or value&1:raise ValueError("Copper MOVE register must be even $080..$1fe")
 return value
def move(reg,value):return (register(reg),int(value)&0xffff)
def wait(v,h=0,vmask=0xff,hmask=0xfe):
 if not 0<=v<=255 or not 0<=h<=254:raise ValueError("WAIT position out of range")
 return (((v&0xff)<<8)|(h&0xfe)|1,((vmask&0x7f)<<8)|(hmask&0xfe))
def skip(v,h=0,vmask=0xff,hmask=0xfe):
 a,b=wait(v,h,vmask,hmask);return (a,b|1)
def end():return (0xffff,0xfffe)
def emit_asm(commands,label="CopperList"):
 lines=["    cnop 0,2",label+":"]
 for kind,args in commands:
  fn={"move":move,"wait":wait,"skip":skip,"end":end}[kind];words=fn(*args)
  comment=kind.upper()
  if kind=="move":comment+=" "+str(args[0]).upper()
  lines.append("    dc.w $%04x,$%04x    ; %s"%(words[0],words[1],comment))
 lines += [label+"_end:",label+"_size equ "+label+"_end-"+label]
 return "\n".join(lines)+"\n"
