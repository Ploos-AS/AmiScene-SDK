# AmiCopper native

Native classic-Amiga front end for AmiScene Copper work.

M0 establishes a small, dependency-light application boundary before GUI toolkit code is added. The target is a keyboard-first native GUI with an `AMICOPPER` ARexx port; the Copper parser/encoder semantics remain shared with the SDK specification rather than hidden in widgets.

Initial modules:
- `src/main.c` application skeleton
- `src/document.c` explicit document/dirty-state model
- `include/amicopper.h` public native-tool state/API

No MUI dependency. No target-runtime dependency on this application.
