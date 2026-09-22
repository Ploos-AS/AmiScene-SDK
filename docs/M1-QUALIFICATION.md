# M1 Qualification

M1 qualification locks the data contracts needed before AmiCopper work begins.

## Qualified contracts

- Amiga planar pixels use MSB-first pixel ordering within each byte.
- Plane 0 is the least-significant color-index bit.
- Interleaved output orders plane bytes per scanline position.
- OCS palette output is 12-bit RGB in `$RGB` word form.
- ASM assets expose aligned labels plus end/size symbols.
- Binary assets are intended for `incbin`.
- ILBM supports uncompressed and ByteRun1 BODY data and roundtrips without changing planar bytes.

## Golden patterns

The tests include known 1-plane and 2-plane byte patterns rather than validating the converter against itself. This is important: a roundtrip alone can preserve the same bug in both directions.

## Scope boundary

M1 qualifies host-side asset representation. It does not claim cycle-exact display qualification on physical Amiga hardware; that belongs to later runtime/effect qualification.
