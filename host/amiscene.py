#!/usr/bin/env python3
import argparse
from amiscene.table import sine,cosine,emit_asm
def main():
    p=argparse.ArgumentParser(prog="amiscene",description="ASM-first Amiga demoscene toolkit")
    p.add_argument("--version",action="version",version="AmiScene SDK 0.1.0-m1")
    sub=p.add_subparsers(dest="command"); t=sub.add_parser("table")
    t.add_argument("kind",choices=("sine","cosine"));t.add_argument("--entries",type=int,default=256);t.add_argument("--amplitude",type=int,default=32767);t.add_argument("--label",default="table");t.add_argument("--directive",choices=("dc.b","dc.w","dc.l"),default="dc.w")
    for name in ("image","copper","blit","pack","build","run","profile","disk"):sub.add_parser(name)
    a=p.parse_args()
    if a.command is None:p.print_help();return 0
    if a.command=="table":
        values=(sine if a.kind=="sine" else cosine)(a.entries,a.amplitude);print(emit_asm(values,a.label,a.directive),end="");return 0
    print("amiscene "+a.command+": planned");return 0
if __name__=="__main__":raise SystemExit(main())
