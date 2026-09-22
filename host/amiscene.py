#!/usr/bin/env python3
"""AmiScene SDK M0 command-line skeleton."""
import argparse

COMMANDS=("image","table","copper","blit","pack","build","run","profile","disk")

def main():
    p=argparse.ArgumentParser(prog="amiscene",description="AmiScene SDK")
    p.add_argument("--version",action="version",version="AmiScene SDK M0")
    sub=p.add_subparsers(dest="command")
    for name in COMMANDS:
        sub.add_parser(name,help=f"{name} tool (planned)")
    a=p.parse_args()
    if a.command is None:
        p.print_help()
        return 0
    print(f"amiscene {a.command}: not implemented in M0")
    return 0

if __name__=="__main__":
    raise SystemExit(main())
