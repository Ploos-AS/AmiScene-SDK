; AmiScene M3 OCS Blitter line-mode octant-0 smoke qualification.
; Deliberately mirrors the known-good blit_line_qualify harness: no Exec,
; allocation, oracle loop or cleanup. This isolates the line parameters.
        include "amiscene/ocs.i"
        xref    AmiBlitLineStart
        xref    AmiBlitWait

Start:
        lea     CUSTOM,a6
        lea     LineDesc(pc),a0
        lea     Bitmap(pc),a3
        lea     Bitmap(pc),a4
        bsr     AmiBlitLineStart
        bsr     AmiBlitWait
        moveq   #0,d0
        rts

        even
LineDesc:
        dc.w    $0b4a,$0059
        dc.w    $ffff,$ffff
        dc.w    -20,12
        dc.w    40,40
        dc.w    -4
        dc.w    $8000,$ffff
        dc.w    $0242

        cnop    0,4
Bitmap:
        dcb.b   640,0
