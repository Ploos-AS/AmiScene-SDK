# AmiScene SDK Roadmap

## M0 — Foundation
- [x] A500/OCS/68000 baseline
- [x] Host/native/runtime architecture
- [x] CLI skeleton and licensing policy
- [x] ASM-first Scene Manifesto
- [x] Assembly-oriented repository layout

## M1 — AmiTable + AmiBitplane
- [x] Deterministic table and planar cores
- [x] Assembly-native output and CLI integration
- [x] PNG/ILBM ingestion and palette workflow
- [x] ILBM read/write + ByteRun1 tests
- [x] Host CI/package qualification

**Status: host-qualified; v0.1.0 tag pending.**

## M2 — AmiCopper
- [x] MOVE/WAIT/SKIP/END encoder
- [x] .copper parser and readable ASM generation
- [x] OCS register validation and scene-oriented diagnostics
- [x] CLI source/check/output workflow
- [x] Minimal 68000 Copper install/start/stop runtime
- [x] DMA save/restore helpers
- [x] A500/OCS reference source and qualification procedure
- [x] Host CLI/parser/generator pipeline PASS (Python 3.10–3.13)
- [ ] A500/OCS emulator runtime PASS

## M3 — AmiBlit
Blitter minterms, masks, shifts, modulos, timing guidance and ASM-oriented code/data generation.

## M4 — AmiRaster + AmiCycle
PAL raster budgets, 68000 timing analysis and DMA/contention-aware profiling.

## M5 — Native scene tools
Focused AmigaOS 2.04+/68000 utilities useful on real machines and emulators.

## M6 — ASM runtime
Small removable 68k routines: startup/takeover, Copper, Blitter, bitplanes, sprites, raster waits, interrupts, DMA, Paula, math, sync and depacking.

## M7 — Assets, audio and sync
Packing, Paula conversion and compact timeline/event data with ASM-first integration.

## M8 — Disk productions
Bootblock, disk builder and clean-room trackloader workflows, including size-focused production support.

## M9 — Qualification + reference effects
Emulator matrix, real-hardware records and readable effects demonstrating the SDK without becoming a demo-maker.

## v1.0
Stable ASM interfaces/formats, documented timing/register contracts and a production-ready A500/OCS workflow.
