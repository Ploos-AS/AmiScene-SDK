"""Lookup-table generators for AmiScene."""
import math

def sine(entries=256, amplitude=32767):
    if entries <= 0: raise ValueError("entries must be positive")
    return [round(math.sin(2*math.pi*i/entries)*amplitude) for i in range(entries)]

def cosine(entries=256, amplitude=32767):
    if entries <= 0: raise ValueError("entries must be positive")
    return [round(math.cos(2*math.pi*i/entries)*amplitude) for i in range(entries)]

def emit_asm(values, label="table", directive="dc.w"):
    body="\n".join(f"    {directive} {v}" for v in values)
    return f"{label}:\n{body}\n"
