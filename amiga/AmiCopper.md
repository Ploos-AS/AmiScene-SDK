# AmiCopper native Amiga tool

AmiCopper is the reference implementation for AmiScene native-tool UX.

## Goals

The tool must feel useful to an Amiga democoder rather than hiding the machine behind a generic application framework.

- Fast, keyboard-first editing with a conventional Amiga GUI.
- Copper instructions remain visible as MOVE, WAIT, SKIP and END.
- Register names and raw custom-register addresses are both supported.
- Immediate validation and useful line-specific diagnostics.
- PAL raster preview with beam position and COLOR changes.
- Cycle/DMA-sensitive information is shown where it matters.
- Generated assembly is readable and remains the canonical interchange.
- No MUI requirement. Keep dependencies small and suitable for classic systems.
- GUI actions must map cleanly to ARexx and file/CLI workflows.

## Initial GUI

The first useful screen should contain:

1. **Copper list editor** — instruction rows with opcode, raster position/register and value/masks.
2. **Source view** — editable textual Copper source using the host-tool grammar.
3. **Raster preview** — PAL frame/raster visualization, initially focused on COLOR00..COLOR31 changes.
4. **Inspector** — decoded instruction words, register address/name, masks, BFD and validation messages.
5. **Export/build controls** — save source, export readable ASM, and invoke configured build workflow.

The editor and source view represent the same document. Neither is a hidden proprietary project format.

## Keyboard workflow

Common operations must be possible without reaching for the mouse: navigate instructions, insert MOVE/WAIT/SKIP, edit operands, validate, save and export. Exact shortcuts will be documented once the native UI toolkit is selected.

## ARexx

Default public port: `AMICOPPER`.

The port is part of the supported interface and is versioned with the tool.

Initial common commands:

| Command | Purpose |
| --- | --- |
| `VERSION` | Return tool/API version. |
| `STATUS` | Return current document/validation state. |
| `OPEN path` | Open Copper source. |
| `SAVE [path]` | Save Copper source. |
| `VALIDATE` | Validate the current Copper list. |
| `EXPORT ASM path [LABEL name]` | Export readable assembler source. |
| `GET key` | Query documented state. |
| `SET key value` | Change documented editable state. |
| `BUILD` | Invoke the configured build action. |
| `QUIT [FORCE]` | Close the tool, respecting unsaved state unless forced. |

Tool-specific commands will be added only where they expose genuinely useful Copper operations.

### Return convention

- ARexx RC 0: success.
- Non-zero RC: documented failure.
- Query results use the ARexx result string.
- Errors return a concise machine-readable token followed by human-readable detail where practical.
- Commands must be deterministic enough for build/asset scripts; GUI prompts must not unexpectedly block non-interactive ARexx use.

## Layer boundary

ARexx and the GUI belong to the native Amiga tooling layer. Generated Copper lists and AmiScene runtime routines do not depend on ARexx, AmigaOS GUI libraries or AmiCopper itself.

A demo coder must remain free to generate a list, hand-edit the assembly, include only the runtime routine they want, and never launch the GUI.
