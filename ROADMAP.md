# AmiScene SDK Roadmap

## M0 — Foundation
- [x] A500/OCS/68000 baseline
- [x] Host/native/runtime architecture
- [x] CLI skeleton and licensing policy
- [x] ASM-first Scene Manifesto
- [x] Assembly-oriented repository layout

## M1 — AmiTable + AmiBitplane
- [x] Initial deterministic table core
- [x] Initial chunky/indexed to planar core
- [x] Assembly-native output formats and labels
- [x] CLI integration
- [x] PNG/ILBM ingestion
- [ ] palette and planar workflow qualification
- [x] ILBM read/write + ByteRun1 roundtrip tests

## M2 — AmiCopper
Copper authoring/validation and readable ASM generation. Raster-aware output, not a generic graphics abstraction.

## M3 — AmiBlit
Blitter minterms, masks, shifts, modulos, timing guidance and ASM-oriented code/data generation.

## M4 — AmiRaster + AmiCycle
PAL raster budgets, 68000 timing analysis and DMA/contention-aware profiling.

## M5 — Native scene tools
Focused AmigaOS 2.04+/68000 utilities useful on real machines and emulators.

## M6 — ASM runtime
Small removable 68k routines: startup/takeover, Copper, Blitter, raster, interrupts, DMA, sprites, Paula, math, sync and depacking.

## M7 — Assets, audio and sync
Packing, Paula conversion and compact timeline/event data with ASM-first integration.

## M8 — Disk productions
Bootblock, disk builder and clean-room trackloader workflows, including size-focused production support.

## M9 — Qualification + reference effects
Emulator matrix, real-hardware records and readable effects demonstrating the SDK without becoming a demo-maker.

## v1.0
Stable ASM interfaces/formats, documented timing/register contracts and a production-ready A500/OCS workflow.
