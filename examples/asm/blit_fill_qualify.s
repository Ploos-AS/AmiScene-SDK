; AmiScene M3 OCS inclusive area-fill qualification.
; One descending word. A contains boundary bits; D must contain the filled span.
        include "amiscene/ocs.i"
        xref    AmiBlitStart
        xref    AmiBlitWait

Start:
        lea     CUSTOM,a6
        lea     FillDesc(pc),a0
        lea     Source(pc),a1
        suba.l  a2,a2
        suba.l  a3,a3
        lea     Dest(pc),a4
        bsr     AmiBlitStart
        bsr     AmiBlitWait
        cmp.w   #$07f8,Dest
        bne.s   .fail
        moveq   #0,d0
        rts
.fail:
        moveq   #1,d0
        rts

        even
FillDesc:
        dc.w    $09f0,$000a        ; A+D, A copy minterm; IFE + DESC
        dc.w    $ffff,$ffff
        dc.w    0,0,0,0
        dc.w    $0041              ; 1 line, 1 word
        cnop    0,4
Source:
        dc.w    $0408              ; inclusive fill toggles between boundary bits
Dest:
        dc.w    0
