# Architecture

AmiScene is a 68k ASM-first demoscene SDK. The hardware model is part of the interface rather than something to abstract away.

## include/

Assembler-facing definitions and macros. Interfaces should remain simple enough to copy into independent scene sources.

## runtime/asm/

Small target-side assembly routines organized by hardware area and target. A routine should be usable independently and document registers, clobbers, memory assumptions and timing/size characteristics where practical.

The OCS/68000 path is canonical. ECS and AGA additions are explicit.

## host/

Heavy conversion, generation, optimization, packing and profiling run on modern hosts. Linux is first-class initially. Host implementation language is not part of the target ABI.

Host output should favor readable assembler, raw binary and incbin-friendly formats.

## amiga/

Native Amiga development/inspection utilities exist when running on the actual platform adds value. Baseline is AmigaOS 2.04+ and 68000 where practical.

## examples/asm/

Examples teach direct hardware programming and SDK routine usage. They should remain readable and include scene-relevant effects and production patterns rather than hiding them behind a framework.

## Qualification

Emulator tests provide reproducibility and CI. Physical hardware remains a separate qualification tier for timing-sensitive code.

See ../SCENE-MANIFESTO.md and TARGETS.md.
