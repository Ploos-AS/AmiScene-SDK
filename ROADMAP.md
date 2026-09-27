# AmiScene SDK Roadmap

AmiScene remains a **68k ASM-first, hardware-first** demoscene SDK. Tools remove repetitive work; they do not hide Copper, Blitter, DMA, raster timing, Paula or memory placement.

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
- [x] m68k Hunk guest runtime PASS via qualified free AROS/FS-UAE CI harness

**Status: complete.** Host CI #152 executed `amiscene-copper-qualify` in the m68k guest with `guest_payload_executed=true` and `status=PASS`. The payload remains 68000/OCS-targeted; the free CI guest host is the qualified A1200/020 AROS profile. A strict A500/OCS/PAL emulator/hardware matrix remains an M12 qualification deliverable.

## M3 — AmiBlit
Blitter tooling and small ASM helpers without abstracting the Blitter away.

- [x] Blitter minterms and channel selection
- [x] Masks, shifts and modulos
- [ ] Copy/fill/cookie-cut helpers
- [x] Line mode support
- [x] 68000 Hunk build + m68k guest execution gate (Host CI #169, guest RC 0)
- [x] OCS inclusive area-fill guest qualification (Host CI #179, guest RC 0)
- [x] OCS Blitter line-mode guest qualification, horizontal reference path (Host CI #188, guest RC 0)
- [ ] Blitter line-mode octant matrix qualification
- [x] ASM-oriented descriptor/data generation
- [ ] Timing and DMA-contention guidance
- [x] Readable copy/cookie-cut reference descriptors and executable A→D copy qualification

## M4 — AmiAssets
Extend the deterministic asset pipeline around assembly-friendly output.

- [ ] `amiscene image` production workflow
- [ ] `amiscene font` bitmap-font/scroller conversion
- [ ] `amiscene anim` frame/sprite animation conversion
- [ ] Shared raw/`incbin`/ASM output conventions
- [ ] Palette and memory-layout reports
- [ ] `amiscene vector` mesh/vector data as an optional later extension

## M5 — AmiPaula
Make audio a first-class hardware pipeline while keeping replay code replaceable.

- [ ] `amiscene sample` conversion/resampling for Paula
- [ ] Period/rate guidance and diagnostics
- [ ] `amiscene mod` inspection/conversion workflow
- [ ] Small Paula runtime helpers
- [ ] Replay adapter contract
- [ ] ProTracker-compatible replay adapter
- [ ] P61 adapter where licensing/integration permits
- [ ] No restricted music, samples or third-party player code without compatible licensing

## M6 — AmiSync
Music/effect synchronization as explicit data and small hooks.

- [ ] Pattern/row/tick counters
- [ ] Pattern-break and marker hooks
- [ ] Named sync events
- [ ] Compact ASM-friendly event tables
- [ ] Example linking Paula/replay events to visual effects

## M7 — AmiDirector + effect ABI
Provide reusable production orchestration without becoming a demo-maker or engine.

- [ ] Define a tiny optional effect ABI: `Init`, `Enter`, `Frame`, `Leave`, `Shutdown`
- [ ] Document register ownership, clobbers, memory ownership and hardware-state contracts
- [ ] `amiscene timeline` compiler for frame/time/sync-event data
- [ ] Simple text/table source format; generated data remains readable
- [ ] Transition/fade helpers as independent routines
- [ ] Effects remain callable directly without the director

## M8 — AmiRaster + AmiDebug
Timing, inspection and real-machine-friendly diagnostics.

- [ ] PAL raster/frame budgets
- [ ] 68000 timing analysis
- [ ] DMA/contention-aware profiling
- [ ] Copper-list vs raster visualization
- [ ] Chip/Fast memory-map and allocation reporting
- [ ] Lightweight serial/parallel logging path for hardware
- [ ] Emulator debugger integration where stable and scriptable
- [ ] `amiscene debug` / `amiscene profile` workflows

## M9 — AmiPack + AmiSize
Production packing and sizecoding support.

- [ ] `amiscene pack`
- [ ] Depacker adapters/routines with explicit licensing
- [ ] `amiscene size`
- [ ] Binary/section/asset size breakdown
- [ ] Machine-readable size reports for CI
- [ ] Optional size-budget regression checks for 4k/64k-style work

## M10 — Build + Run + Profiles
Reproducible end-to-end developer workflow.

- [ ] `amiscene build`
- [ ] `amiscene run`
- [ ] `amiscene profile`
- [ ] Named A500/OCS/PAL reference profiles
- [ ] amiga-dev integration without making it a hidden runtime dependency
- [ ] amiga-runtime integration for reproducible emulator qualification

## M11 — Disk productions
Release-oriented disk workflows.

- [ ] `amiscene disk` ADF builder
- [ ] Bootblock workflow
- [ ] Clean-room trackloader workflow
- [ ] HDF/hard-disk image support where useful for larger productions
- [ ] Deterministic release packaging and size reports

## M12 — Qualification + reference effects
Every shipped building block should have evidence, not just compile.

- [ ] Host tests for deterministic converters/generators
- [ ] m68k reference builds
- [ ] Headless emulator execution of shipped examples in CI
- [ ] A500/OCS/PAL reference runtime matrix
- [ ] Separate real-hardware qualification records
- [ ] Timing-sensitive tests explicitly distinguish emulator and hardware evidence

## Cookbook / onboarding
The cookbook is a product deliverable and doubles as an integration-test ladder.

- [ ] Your first Copper bar
- [ ] Raster gradient
- [ ] Hardware sprite
- [ ] Blitter bob / cookie-cut
- [ ] Double buffering
- [ ] Bitmap-font scroller
- [ ] MOD playback
- [ ] Music-synchronized effect
- [ ] Timeline/director mini production
- [ ] Complete small A500 demo

Examples must teach the hardware and remain useful without the director layer.

## Native Amiga UX and ARexx
AmiScene's native tools should be productive scene tools, not framework-heavy applications.

- [ ] Define a common native-tool UI model: keyboard-first, fast GUI, previews, diagnostics, no hidden hardware state.
- [ ] Define a stable ARexx port convention for relevant tools (`AMICOPPER`, `AMIBLIT`, `AMIBITPLANE`, `AMIPALETTE`, etc.).
- [ ] Define common ARexx verbs and return conventions: `OPEN`, `SAVE`, `EXPORT`, `BUILD`, `GET`, `SET`, `STATUS`, `QUIT`.
- [ ] Make query/state operations scriptable, not only actions.
- [ ] Keep ARexx strictly in the native tooling/workflow layer; target runtime remains OS-independent.
- [ ] Ship useful ARexx workflow examples for repeatable asset conversion, export and build loops.
- [ ] Keep GUI, CLI and source workflows interoperable and reproducible.
- [ ] Start native UI work with AmiCopper as the reference implementation.

## v1.0
Stable ASM interfaces/formats, documented timing/register contracts, qualified reference examples and a production-ready A500/OCS/PAL workflow.

C may be supported where useful, but **68k assembly remains the canonical target/runtime ABI**. C-facing wrappers must sit on top of documented ASM interfaces rather than redefine them.
