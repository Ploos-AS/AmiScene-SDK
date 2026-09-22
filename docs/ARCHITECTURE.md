# Architecture

AmiScene SDK has three separate layers.

## Host
Heavy processing belongs on modern hosts. Linux is first-class initially. Host tools perform conversion, optimization, generation, packing, building, launching and profiling.

## Amiga native
Native tools exist when interaction with real Amiga hardware or AmigaOS is useful. Baseline: AmigaOS 2.04+ and 68000 where practical. A host feature does not automatically require a native equivalent.

## Runtime
Small target-side modules for demos and intros. They should minimize dependencies and keep memory use and timing predictable.

## Integration
The CLI is the stable automation surface. GUI applications may use the same libraries and formats. Emulators are development/CI aids and do not replace real-hardware qualification.
