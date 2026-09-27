"""AmiScene command line interface."""
import argparse
from pathlib import Path
from .table import sine,cosine,emit_asm
from .image import build_png,emit_palette_asm,parse_palette
from .ilbm import load_ilbm
from .bitplane import emit_incbin
from .copper import parse as parse_copper,diagnose as diagnose_copper,emit_asm as emit_copper_asm
from .blit import descriptor as blit_descriptor,parse as parse_blit,emit_asm as emit_blit_asm,MINTERMS
def main():
 p=argparse.ArgumentParser(prog="amiscene",description="ASM-first Amiga demoscene toolkit");p.add_argument("--version",action="version",version="AmiScene SDK 0.1.0");sub=p.add_subparsers(dest="command")
 t=sub.add_parser("table");t.add_argument("kind",choices=("sine","cosine"));t.add_argument("--entries",type=int,default=256);t.add_argument("--amplitude",type=int,default=32767);t.add_argument("--label",default="table");t.add_argument("--directive",choices=("dc.b","dc.w","dc.l"),default="dc.w")
 im=sub.add_parser("image");im.add_argument("input");im.add_argument("--planes",type=int);im.add_argument("--layout",choices=("interleaved","separate"),default="interleaved");im.add_argument("--output",required=True);im.add_argument("--asm");im.add_argument("--label",default="bitmap");im.add_argument("--palette");im.add_argument("--dither",action="store_true")
 cp=sub.add_parser("copper");cp.add_argument("input",nargs="?");cp.add_argument("--demo",action="store_true");cp.add_argument("--label",default="CopperList");cp.add_argument("-o","--output");cp.add_argument("--check",action="store_true")
 bl=sub.add_parser("blit");bl.add_argument("input",nargs="?");bl.add_argument("--channels",default="ad");bl.add_argument("--minterm",default="copy_a");bl.add_argument("--ashift",type=int,default=0);bl.add_argument("--bshift",type=int,default=0);bl.add_argument("--afwm",default="$ffff");bl.add_argument("--alwm",default="$ffff");bl.add_argument("--amod",type=int,default=0);bl.add_argument("--bmod",type=int,default=0);bl.add_argument("--cmod",type=int,default=0);bl.add_argument("--dmod",type=int,default=0);bl.add_argument("--width",type=int,default=1);bl.add_argument("--height",type=int,default=1);bl.add_argument("--label",default="BlitDesc");bl.add_argument("-o","--output")
 for name in ("pack","build","run","profile","disk"):sub.add_parser(name)
 a=p.parse_args()
 if a.command is None:p.print_help();return 0
 if a.command=="table":
  values=(sine if a.kind=="sine" else cosine)(a.entries,a.amplitude);print(emit_asm(values,a.label,a.directive),end="");return 0
 if a.command=="copper":
  if a.demo:commands=[("wait",(44,0)),("move",("COLOR00",0x003)),("wait",(100,0)),("move",("COLOR00",0x00f)),("end",())]
  elif a.input:commands=parse_copper(Path(a.input).read_text(encoding="utf-8"))
  else:raise ValueError("copper requires an input file or --demo")
  d=diagnose_copper(commands)
  if d["errors"]:raise ValueError("\n".join(d["errors"]))
  for warning in d["warnings"]:print("warning: "+warning)
  if a.check:print("OK: %d Copper commands, %d warning(s)"%(len(commands),len(d["warnings"])));return 0
  asm=emit_copper_asm(commands,a.label)
  if a.output:Path(a.output).write_text(asm,encoding="utf-8")
  else:print(asm,end="")
  return 0
 if a.command=="blit":
  mt=MINTERMS[a.minterm] if a.minterm in MINTERMS else int(a.minterm[1:],16) if a.minterm.startswith("$") else int(a.minterm,0)
  word=lambda v:int(v[1:],16) if isinstance(v,str) and v.startswith("$") else int(v,0) if isinstance(v,str) else int(v)
  d=parse_blit(Path(a.input).read_text(encoding="utf-8")) if a.input else blit_descriptor(channels=a.channels,minterm=mt,ashift=a.ashift,bshift=a.bshift,afwm=word(a.afwm),alwm=word(a.alwm),amod=a.amod,bmod=a.bmod,cmod=a.cmod,dmod=a.dmod,width=a.width,height=a.height)
  asm=emit_blit_asm(d,a.label)
  if a.output:Path(a.output).write_text(asm,encoding="utf-8")
  else:print(asm,end="")
  return 0
 if a.command=="image":
  if Path(a.input).suffix.lower() in (".iff",".ilbm",".lbm"):
   asset=load_ilbm(a.input)
   if a.planes is not None and a.planes!=asset["planes"]:raise ValueError("--planes does not match ILBM")
  else:
   if a.planes is None:raise ValueError("--planes is required for PNG input")
   asset=build_png(a.input,a.planes,a.layout,parse_palette(a.palette) if a.palette else None,a.dither)
  Path(a.output).write_bytes(asset["data"])
  if a.asm:
   asm=emit_incbin(Path(a.output).name,a.label)+emit_palette_asm(asset["palette"],a.label+"_palette");asm+=a.label+"_width equ %d\n%s_height equ %d\n%s_planes equ %d\n" % (asset["width"],a.label,asset["height"],a.label,asset["planes"]);Path(a.asm).write_text(asm)
  return 0
 print("amiscene "+a.command+": planned");return 0
