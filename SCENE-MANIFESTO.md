# AmiScene Scene Manifesto

AmiScene exists for people who want to code the Amiga, not hide it.

## ASM first

Motorola 68000 assembly is the primary target language. Host tools may use other languages, but their output must serve assembly workflows: readable labels, includes, `dc.*` data, offsets and `incbin`-friendly assets.

C support may be added where useful, but it must not dictate the runtime architecture.

## Hardware first

Copper, Blitter, bitplanes, sprites, DMA, interrupts, raster timing and Paula are exposed as Amiga hardware concepts. AmiScene must not bury them behind generic graphics/audio abstractions.

## Source over black boxes

Runtime routines must be readable, reusable and removable. A coder should be able to take one routine, understand its register contract, modify it and use it without adopting the rest of AmiScene.

Generated assembly should be human-readable.

## Cycles and bytes matter

Performance-sensitive routines should document, where practical:

- target chipset and CPU
- register inputs/outputs and clobbers
- memory requirements and alignment
- Chip/Fast RAM assumptions
- approximate byte size
- timing/cycle characteristics and important contention assumptions

## A500 means A500

The reference target is 68000 + OCS + PAL on A500-class hardware. Baseline code must not silently depend on 68020 instructions, AGA/ECS features, Fast RAM, accelerators, RTG or emulator behavior.

## Demo runtime, not application framework

Runtime code should work without AmigaOS dependencies where a demo requires takeover or bare-metal-style operation. Native development utilities may use AmigaOS.

## Sizecoding is first-class

AmiScene should support workflows where bytes matter. Small intros, compact data representation, depackers and size/speed alternatives belong in the design.

## Emulators do not define the hardware

Emulators are essential development and CI tools. Passing emulator tests is not automatically proof of exact physical-machine timing. Real-hardware qualification should be recorded separately.

## Tools help the coder

AmiScene is not a click-to-make-a-demo product. Generators, converters, profilers and examples should remove repetitive work while leaving creative and technical control with the coder.

## Earn trust through useful code

The project should favor small excellent routines, accurate documentation, reproducible results and real productions over broad feature counts.
