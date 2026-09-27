; AmiScene M3 automated OCS Blitter qualification payload
; Copies four words A -> D with minterm $f0, then verifies every result word.
        include "amiscene/ocs.i"
        xref    AmiBlitStart
        xref    AmiBlitWait

Start:
        lea     CUSTOM,a6
        lea     BlitDesc(pc),a0
        lea     Source(pc),a1
        suba.l  a2,a2
        suba.l  a3,a3
        lea     Dest(pc),a4
        bsr     AmiBlitStart
        bsr     AmiBlitWait

        lea     Source(pc),a0
        lea     Dest(pc),a1
        moveq   #3,d1
.verify:
        cmpm.w  (a0)+,(a1)+
        bne.s   .fail
        dbf     d1,.verify
        moveq   #0,d0
        rts
.fail:
        moveq   #1,d0
        rts

        even
BlitDesc:
        dc.w    $09f0,$0000
        dc.w    $ffff,$ffff
        dc.w    $0000,$0000,$0000,$0000
        dc.w    $0044              ; height 1, width 4 words

        cnop    0,4
Source:
        dc.w    $1234,$abcd,$55aa,$f00f
Dest:
        dc.w    0,0,0,0
