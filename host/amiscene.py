#!/usr/bin/env python3
import argparse
from pathlib import Path
from amiscene.table import sine,cosine,emit_asm
from amiscene.image import build_png,emit_palette_asm,parse_palette
from amiscene.bitplane import emit_incbin
def main():
 p=argparse.ArgumentParser(prog="amiscene",description="ASM-first Amiga demoscene toolkit");p.add_argument("--version",action="version",version="AmiScene SDK 0.1.0-m1");sub=p.add_subparsers(dest="command")
 t=sub.add_parser("table");t.add_argument("kind",choices=("sine","cosine"));t.add_argument("--entries",type=int,default=256);t.add_argument("--amplitude",type=int,default=32767);t.add_argument("--label",default="table");t.add_argument("--directive",choices=("dc.b","dc.w","dc.l"),default="dc.w")
 im=sub.add_parser("image");im.add_argument("input");im.add_argument("--planes",type=int,required=True);im.add_argument("--layout",choices=("interleaved","separate"),default="interleaved");im.add_argument("--output",required=True);im.add_argument("--asm");im.add_argument("--label",default="bitmap");im.add_argument("--palette");im.add_argument("--dither",action="store_true")
 for name in ("copper","blit","pack","build","run","profile","disk"):sub.add_parser(name)
 a=p.parse_args()
 if a.command is None:p.print_help();return 0
 if a.command=="table":
  values=(sine if a.kind=="sine" else cosine)(a.entries,a.amplitude);print(emit_asm(values,a.label,a.directive),end="");return 0
 if a.command=="image":
  pal=parse_palette(a.palette) if a.palette else None;asset=build_png(a.input,a.planes,a.layout,pal,a.dither);Path(a.output).write_bytes(asset["data"])
  if a.asm:
   asm=emit_incbin(Path(a.output).name,a.label)+emit_palette_asm(asset["palette"],a.label+"_palette");asm+=a.label+"_width equ %d\n%s_height equ %d\n%s_planes equ %d\n" % (asset["width"],a.label,asset["height"],a.label,asset["planes"]);Path(a.asm).write_text(asm)
  return 0
 print("amiscene "+a.command+": planned");return 0
if __name__=="__main__":raise SystemExit(main())
