; AmiScene M3 OCS Blitter pixel-exact line-octant qualification.
        include "amiscene/ocs.i"
        xref AmiBlitLineStart
        xref AmiBlitWait
Start:
        lea CUSTOM,a6
        lea Cases(pc),a5
        lea Bitmaps(pc),a2
        lea Starts(pc),a1
        lea Expected(pc),a0
        moveq #7,d7
.case:
        move.w (a1)+,d6
        lea 120(a2),a3
        adda.w d6,a3
        move.l a3,a4
        move.l a0,-(sp)
        move.l a5,a0
        bsr AmiBlitLineStart
        bsr AmiBlitWait
        move.l (sp)+,a0
        lea 120(a2),a3
        moveq #8,d5
.row:
        cmp.w (a0)+,(a3)
        bne.s .fail
        adda.w #40,a3
        dbra d5,.row
        add.l #24,a5
        add.l #600,a2
        dbra d7,.case
        moveq #0,d0
        rts
.fail:  moveq #1,d0
        rts

; y1*40 offsets. x1 stays within the first word; BLTCON0 START handles x.
Starts: dc.w 0,0,0,0,320,320,320,320

; major=8, minor=3: APT=-10, AMOD=-20, BMOD=12, size=(9<<6)|2.
Cases:
        dc.w $0b4a,$0059,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0045,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $8b4a,$004d,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $8b4a,$005d,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $8b4a,$0055,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $8b4a,$0049,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0041,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0051,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242

; Independent integer-Bresenham oracle, one 16-pixel word for rows y=0..8.
Expected:
        dc.w $c000,$3000,$0e00,$0180,0,0,0,0,0
        dc.w $8000,$8000,$4000,$4000,$2000,$2000,$2000,$1000,$1000
        dc.w $0080,$0080,$0100,$0100,$0200,$0200,$0200,$0400,$0400
        dc.w $0180,$0600,$3800,$c000,0,0,0,0,0
        dc.w 0,0,0,0,0,$c000,$3800,$0600,$0180
        dc.w $0400,$0400,$0200,$0200,$0200,$0100,$0100,$0080,$0080
        dc.w $1000,$1000,$2000,$2000,$2000,$4000,$4000,$8000,$8000
        dc.w 0,0,0,0,0,$0180,$0e00,$3000,$c000
        cnop 0,4
Bitmaps: dcb.b 4800,0
