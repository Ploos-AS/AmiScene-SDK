# AmiScene SDK

**68k ASM-first, hardware-first demoscene SDK and toolchain for Commodore Amiga.**

AmiScene is built for coders who want direct control of the machine. It provides readable/reusable assembly runtime code plus host and native tools that remove repetitive work without hiding Copper, Blitter, DMA, raster timing, Paula or the rest of the hardware.

## Reference target

- Amiga 500 class
- Motorola 68000
- OCS
- PAL first
- 1 MiB RAM where practical

ECS and AGA/A1200 are explicit extensions. C may be supported later, but 68k assembly defines the runtime design.

Read the [Scene Manifesto](SCENE-MANIFESTO.md).

## Tool layers

- `include/` assembly includes, register definitions and macros
- `runtime/asm/` small reusable 68k routines
- `host/` generators, converters, profilers and build tools
- `amiga/` native Amiga utilities where hardware/native use adds value
- `examples/asm/` readable scene-oriented assembly examples
- `tests/` host, emulator and real-hardware qualification support

## Planned CLI

```text
amiscene image
amiscene table
amiscene copper
amiscene blit
amiscene pack
amiscene build
amiscene run
amiscene profile
amiscene disk
```

Host tools should emit assembly-friendly data: labels, `dc.b/dc.w/dc.l`, offsets, includes and `incbin`-ready assets.

No proprietary Kickstart ROMs, AmigaOS files, restricted demo assets or malware belong in this repository.

See [ROADMAP.md](ROADMAP.md), [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) and [LICENSES.md](LICENSES.md).
