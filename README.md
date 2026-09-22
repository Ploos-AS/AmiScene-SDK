# AmiScene SDK

Modern demoscene-oriented SDK and toolchain for Commodore Amiga development.

## M0 baseline

- Primary target: Amiga 500 class, Motorola 68000, OCS, PAL, 1 MiB RAM where practical
- Linux host tools first; Windows and macOS planned
- Native Amiga tools where running on real hardware adds value
- Small target-side runtime components
- CLI-first, scriptable workflows and emulator-assisted qualification
- ECS and AGA/A1200 are explicit extensions

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

## Layout

- `host/` host-side tools and CLI
- `amiga/` native Amiga utilities
- `runtime/` target-side runtime
- `examples/` example productions
- `docs/` architecture and target documentation
- `tests/` host, emulator and native qualification

No proprietary Kickstart ROMs, AmigaOS files, restricted demo assets or malware belong in this repository.

See [ROADMAP.md](ROADMAP.md), [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) and [LICENSES.md](LICENSES.md).
