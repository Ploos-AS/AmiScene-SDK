; AmiScene M3 OCS Blitter line octant runtime qualification.
; Eight independent line draws. Each case returns through CheckNonZero;
; this first matrix gate proves that every octant advances and writes bitmap data.
        include "amiscene/ocs.i"
        xref    AmiBlitLineStart
        xref    AmiBlitWait

Start:
        lea     CUSTOM,a6
        lea     Cases(pc),a5
        lea     Bitmaps(pc),a2
        moveq   #7,d7
.loop:
        move.l  a5,a0
        move.l  a2,a3
        adda.l  #280,a3
        move.l  a3,a4
        bsr     AmiBlitLineStart
        bsr     AmiBlitWait
        moveq   #0,d0
        move.w  #299,d1
.scan:
        or.w    (a2)+,d0
        dbra    d1,.scan
        tst.w   d0
        beq.s   .fail
        add.l   #24,a5
        add.l   #600,a2
        dbra    d7,.loop
        moveq   #0,d0
        rts
.fail:
        moveq   #1,d0
        rts

; Descriptor layout is the AmiBlitLineStart ABI.
; Common geometry uses major=8, minor=3: err=-10, AMOD=-20, BMOD=12.
; BLTCON1 octant bits: 18,04,0c,1c,14,08,00,10 plus SIGN=$40 and LINE=1.
Cases:
        dc.w $0b4a,$0059,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0045,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$004d,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$005d,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0055,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0049,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0041,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242
        dc.w $0b4a,$0051,$ffff,$ffff,-20,12,40,40,-10,$8000,$ffff,$0242

        cnop 0,4
Bitmaps:
        dcb.b 4800,0
