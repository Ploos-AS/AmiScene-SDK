; AmiScene M3 OCS Blitter octant-0 AllocMem smoke qualification.
; Isolates dynamic Chip RAM from the larger octant oracle harness.
        include "amiscene/ocs.i"
        xref    AmiBlitLineStart
        xref    AmiBlitWait

Start:
        move.l  4.w,a6
        move.l  #640,d0
        move.l  #$10002,d1       ; MEMF_CHIP|MEMF_CLEAR
        jsr     -198(a6)          ; Exec AllocMem()
        tst.l   d0
        beq.s   .alloc_fail
        move.l  d0,a2

        lea     CUSTOM,a6
        lea     LineDesc(pc),a0
        move.l  a2,a3
        move.l  a2,a4
        bsr     AmiBlitLineStart
        bsr     AmiBlitWait

        move.l  4.w,a6
        move.l  a2,a1
        move.l  #640,d0
        jsr     -210(a6)          ; Exec FreeMem(address,size)
        moveq   #0,d0
        rts

.alloc_fail:
        moveq   #2,d0
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
