# amiga-runtime integration

M2 runtime qualification uses the shared `Ploos-AS/amiga-runtime` infrastructure rather than embedding an emulator or ROM in AmiScene.

Canonical target:

- profile: `amiga-ocs-68000-1m.conf`
- CPU: 68000
- chipset: OCS
- video: PAL
- memory: 1 MiB class
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
amiga-runtime test examples/asm/build/amiscene-copper --profile amiga-ocs-68000-1m --runtime fs-uae
```

ROM/Workbench material is supplied outside this repository. No proprietary Amiga files are committed.

A runtime PASS must record actual emulator evidence. Merely building the binary or passing host CI is not an M2 runtime PASS.
