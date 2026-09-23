# amiga-runtime integration

M2 runtime qualification uses the shared `Ploos-AS/amiga-runtime` infrastructure rather than embedding an emulator or ROM in AmiScene.

Canonical target:

- profile: `amiga-ocs-68000-1m.conf`
- free runtime: AROS m68k ROM/runtime
- CPU: 68000
- chipset: OCS
- video: PAL
- memory: 512 KiB Chip + 512 KiB Fast (1 MiB class)
- reference: `examples/asm/copper_minimal.s`

## Build

The example Makefile expects the Ploos-AS Bebbo/m68k-amigaos toolchain:

```sh
make -C examples/asm
```

The produced program is `examples/asm/build/amiscene-copper`.

## Runtime handoff

With `amiga-runtime` available:

```sh
amiga-runtime test-hunk examples/asm/build/amiscene-copper --profile amiga-ocs-68000-1m
```

ROM/Workbench material is supplied outside this repository. No proprietary Amiga files are committed.

The Hunk path boots the redistributable AROS m68k runtime and launches the native Amiga Hunk executable without requiring a `--version` application interface.\n\nAn AROS m68k runtime PASS must record actual emulator evidence. Merely building the binary or passing host CI is not an M2 runtime PASS. AROS qualification is the redistributable CI baseline and must not be reported as AmigaOS/Kickstart compatibility qualification; those remain separate qualification axes.
