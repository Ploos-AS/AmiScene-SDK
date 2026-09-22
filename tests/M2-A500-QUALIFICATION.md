# M2 A500/OCS qualification

Reference program: `examples/asm/copper_minimal.s`.

## Target

- Motorola 68000
- OCS
- PAL
- A500-class machine
- Copper list in Chip RAM
- no AmigaOS API dependency inside the Copper runtime

## Expected visible result

The reference Copper list changes `COLOR00` at several raster positions. A successful run shows stable horizontal background-color bands. The left mouse button exits the reference loop.

## Runtime checks

1. Assemble/link the reference with `runtime/asm/ocs/copper.s`.
2. Place executable/code/data so the Copper list is in Chip-accessible memory.
3. Run under the canonical A500/OCS PAL emulator profile.
4. Confirm stable raster bars for multiple frames.
5. Confirm left mouse exits.
6. Confirm the caller can restore its prior environment/state.
7. Record emulator/version, Kickstart environment, memory configuration and result.

## Boundaries

This reference deliberately does not pretend to be a complete AmigaOS-friendly takeover framework. The Copper runtime exposes small hardware routines. A later startup/takeover module owns OS suspension, interrupt state and complete machine restoration.

Emulator PASS qualifies the reference path but is not a claim of physical-hardware timing qualification.
