; AmiScene M3 OCS Blitter octant-0 AllocMem + oracle qualification.
; Adds only pixel verification to the known-good dynamic Chip RAM smoke test.
        include "amiscene/ocs.i"
        xref    AmiBlitLineStart
        xref    AmiBlitWait

Start:
        move.l  4.w,a6
        move.l  #640,d0
        move.l  #$10002,d1
        jsr     -198(a6)
        tst.l   d0
        beq.s   .alloc_fail
        move.l  d0,a2

        lea     CUSTOM,a6
        lea     LineDesc(pc),a0
        move.l  a2,a3
        move.l  a2,a4
        bsr     AmiBlitLineStart
        bsr     AmiBlitWait

        ; Verify the first two oracle rows only.  This adds one pointer
        ; step and comparison without the DBRA loop used by the full test.
        lea     Expected(pc),a0
        move.l  a2,a3
        move.w  (a0)+,d0
        cmp.w   (a3),d0
        bne.s   .mismatch
        adda.w  #40,a3
        move.w  (a0)+,d0
        cmp.w   (a3),d0
        bne.s   .mismatch
        moveq   #0,d0
        rts
.mismatch:
        moveq   #1,d0
        rts
.alloc_fail:
        moveq   #2,d0
        rts

        even
LineDesc:
        dc.w    $0b4a,$0059,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
Expected:
        dc.w    $c000,$3000,$0e00,$0180,0,0,0,0,0
