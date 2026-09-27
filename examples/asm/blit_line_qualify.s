; AmiScene M3 OCS Blitter line-mode qualification.
; Draw a 16-pixel horizontal line into a zeroed 1-bit bitmap.
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
        cmp.w   #$ffff,Bitmap
        bne.s   .fail
        moveq   #0,d0
        rts
.fail:
        moveq   #1,d0
        rts

        even
LineDesc:
        dc.w    $0b4a,$0059        ; LF + A/B/C/D, LINE+SUD/AUL+SIGN
        dc.w    $ffff,$ffff
        dc.w    -60,0              ; AMOD, BMOD
        dc.w    40,40              ; CMOD, DMOD
        dc.w    -30                ; A error term
        dc.w    $8000,$ffff        ; ADAT, texture
        dc.w    $0402              ; height 16, line-mode width field fixed at 2

        cnop    0,4
Bitmap:
        dc.w    0
        dcb.b   638,0
