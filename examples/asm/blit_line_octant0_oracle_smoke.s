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
        lea     120(a2),a3
        move.l  a3,a4
        bsr     LineStartLowAPT
        bsr     AmiBlitWait

        ; Row 0 compare and row 1 access are known-good.  Compare row 1
        ; explicitly, still without a loop.
        lea     Expected(pc),a0
        move.w  (a0)+,d0
        cmp.w   120(a2),d0
        bne.s   .mismatch
        lea     120(a2),a3
        adda.w  #40,a3
        move.w  (a0),d0
        cmp.w   (a3),d0
        bne.s   .row1_mismatch
        moveq   #0,d0
        rts
.row1_mismatch:
        ; Return the actual row-1 word with a marker for CI diagnostics.
        lea     120(a2),a3
        adda.w  #40,a3
        move.w  (a3),d0
        ori.w   #$8000,d0
        rts
.mismatch:
        moveq   #1,d0
        rts
.alloc_fail:
        moveq   #2,d0
        rts

; Diagnostic line start: identical register setup, but write only
; BLTAPTL for the line error accumulator.
LineStartLowAPT:
        bsr     AmiBlitWait
        move.w  (a0)+,BLTCON0(a6)
        move.w  (a0)+,BLTCON1(a6)
        move.w  (a0)+,BLTAFWM(a6)
        move.w  (a0)+,BLTALWM(a6)
        move.w  (a0)+,BLTAMOD(a6)
        move.w  (a0)+,BLTBMOD(a6)
        move.w  (a0)+,BLTCMOD(a6)
        move.w  (a0)+,BLTDMOD(a6)
        move.w  (a0)+,BLTAPTL(a6)
        move.w  (a0)+,BLTADAT(a6)
        move.w  (a0)+,BLTBDAT(a6)
        move.l  a3,BLTCPTH(a6)
        move.l  a4,BLTDPTH(a6)
        move.w  (a0),BLTSIZE(a6)
        rts

        even
LineDesc:
        dc.w    $0b4a,$0059,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
Expected:
        dc.w    $c000,$3000,$0e00,$0180,0,0,0,0,0
