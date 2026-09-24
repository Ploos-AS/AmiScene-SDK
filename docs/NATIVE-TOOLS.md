# AmiScene native-tool interface conventions

This document defines the shared contract for native Amiga AmiScene tools. Individual tools may extend it, but should not invent incompatible workflow conventions without a strong hardware- or task-specific reason.

## UX principles

Native tools are coder tools.

- Keyboard-first operation; mouse use is optional for normal edit/validate/export loops.
- Use standard Amiga UI conventions and system-friendly libraries where practical.
- No mandatory MUI dependency.
- Keep startup and interaction responsive on classic hardware.
- Show hardware concepts instead of replacing them with generic abstractions.
- Diagnostics identify the relevant source row, asset, register, address or hardware constraint.
- GUI state must not become the only copy of important project data.
- Prefer documented text/raw/ASM formats that can live in source control.

## Document model

A native tool should operate on an inspectable canonical source or asset representation. GUI views are projections of that data, not a proprietary replacement for it.

Save/export operations must make dirty state explicit. Non-interactive automation must never become blocked by an unexpected requester.

## ARexx port naming

Relevant tools expose an uppercase public port derived from the tool name:

- AmiCopper: `AMICOPPER`
- AmiBlit: `AMIBLIT`
- AmiBitplane: `AMIBITPLANE`
- AmiPalette: `AMIPALETTE`
- AmiSprite: `AMISPRITE`
- AmiFont: `AMIFONT`
- AmiWave: `AMIWAVE`
- AmiTrack: `AMITRACK`

If a port name is already occupied, an implementation may use a documented instance suffix. Scripts should be able to query the effective port when launched by another AmiScene tool.

## Common ARexx vocabulary

Tools implement commands only when meaningful, but shared verbs retain shared semantics:

- `VERSION` — tool and ARexx API version.
- `STATUS` — concise current state suitable for automation.
- `OPEN path` — load a canonical source/asset.
- `NEW` — create a new document where meaningful.
- `SAVE [path]` — save canonical editable data.
- `EXPORT format path [...]` — produce a build-facing artifact.
- `VALIDATE` — run tool-specific validation.
- `GET key` — query documented state.
- `SET key value` — modify documented state.
- `BUILD` — invoke the configured project/build action where supported.
- `QUIT [FORCE]` — exit; normal QUIT respects dirty state.

Tool-specific verbs should expose real scene operations rather than generic object-framework internals.

## Return contract

- RC 0 means success.
- Non-zero RC values are failures and are documented per common/tool-specific error class.
- Queries return their value through the ARexx result string.
- Errors should return a stable token plus concise human-readable context.
- Paths containing spaces must be accepted using normal ARexx quoting.
- Batch/script execution must be deterministic and must not require GUI interaction.

## Automation and interoperability

ARexx should make useful production chains possible, for example:

1. open or generate an asset;
2. set conversion parameters;
3. validate hardware constraints;
4. export raw data and readable ASM metadata;
5. ask AmiCopper or another tool to reload generated data;
6. invoke a build;
7. inspect status/result and continue.

This is an automation interface, not a runtime dependency. Target code remains usable without AmigaOS, ARexx or any AmiScene application.

## Scene-facing rule

A GUI convenience must not make the resulting production harder to understand, reproduce, optimize or hand-edit. If an operation changes bytes, cycles, DMA use, memory placement, palette/register state or target requirements, the tool should make that consequence inspectable.
