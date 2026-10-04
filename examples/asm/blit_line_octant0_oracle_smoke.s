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

        ; Single post-Blitter Chip RAM read.  Do not compare or loop yet:
        ; this distinguishes a read hazard from oracle control flow.
        move.w  (a2),d7
        moveq   #0,d0
        rts
.alloc_fail:
        moveq   #2,d0
        rts

        even
LineDesc:
        dc.w    $0b4a,$0059,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
Expected:
        dc.w    $c000,$3000,$0e00,$0180,0,0,0,0,0
