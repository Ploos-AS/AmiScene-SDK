; AmiScene M3 OCS Blitter pixel-exact line-octant qualification.
        include "amiscene/ocs.i"
        xref AmiBlitLineStart
        xref AmiBlitWait
Start:
        move.l 4.w,a6
        move.l #4800,d0
        move.l #$10002,d1       ; MEMF_CHIP|MEMF_CLEAR
        jsr -198(a6)            ; Exec AllocMem()
        tst.l d0
        beq .alloc_fail
        move.l d0,a2
        lea CUSTOM,a6
        lea Cases(pc),a5
        lea Starts(pc),a1
        lea Expected(pc),a0
        ifnd OCTANT
OCTANT  equ -1
        endif
        ifeq OCTANT+1
        moveq #7,d7
        moveq #0,d4            ; all-octants mode
        else
        moveq #0,d7            ; one isolated case
        moveq #OCTANT,d4
        mulu #24,d4
        adda.l d4,a5
        moveq #OCTANT,d4
        mulu #2,d4
        adda.l d4,a1
        moveq #OCTANT,d4
        mulu #18,d4
        adda.l d4,a0
        moveq #OCTANT,d4
        endif
 .case:
        move.w (a1)+,d6        ; bitmap start offset for this octant
        move.w d4,d3
        add.w d3,d3
        move.w Strides(pc,d3.w),d3  ; index by octant, not mutable cursor
        move.w d3,-(sp)
        lea 120(a2),a3
        adda.w d6,a3
        move.l a3,a4           ; AmiBlitLineStart D pointer
        move.l a0,-(sp)
        move.l a5,a0
        bsr AmiBlitLineStart
        ; Bounded wait: never let a bad line-mode octant hang CI forever.
        ; Return 0x40+octant (64..71) when Blitter BUSY does not clear.
        move.l #$00100000,d3
.wait:
        btst #6,DMACONR(a6)
        beq.s .wait_done
        subq.l #1,d3
        bne.s .wait
        move.l (sp)+,a0
        addq.l #2,sp           ; discard saved stride on timeout
        move.w d4,d7
        add.w #$40,d7
        bra.s .done
 .wait_done:
        move.l (sp)+,a0
        lea 120(a2),a3
        move.w (sp)+,d3       ; expected raster stride for this octant
        moveq #8,d5
.row:
        move.w (a0)+,d0
        cmp.w (a3),d0
        bne.s .fail
        adda.w d3,a3
        dbra d5,.row
        add.l #24,a5
        ifeq OCTANT+1
        add.l #600,a2
        addq.w #1,d4
        dbra d7,.case
        endif
        moveq #0,d7
        bra.s .done
.fail:  ; Encode first mismatching raster row as $100 + octant*16 + row.
        ; Distinct from BUSY timeout ($40..$47) and successful RC=0.
        move.w d4,d7
        lsl.w #4,d7
        add.w #9,d7
        sub.w d5,d7
        add.w #$100,d7
.done:
        move.l 4.w,a6
        move.l a2,a1            ; allocation base
        ifeq OCTANT+1
        sub.l #4200,a1          ; all-octants mode advanced a2 seven times
        endif
        move.l #4800,d0
        jsr -210(a6)            ; Exec FreeMem(address,size)
        move.l d7,d0
        rts
.alloc_fail:
        moveq #2,d0
        rts

; y1*40 offsets. x1 stays within the first word; BLTCON0 START handles x.
Starts: dc.w 0,0,0,0,320,320,320,320

; Expected memory raster direction per octant. Kept explicit so the
; qualification does not accidentally impose one screen-Y convention.
Strides: dc.w 40,40,40,-40,-40,-40,-40,-40

; major=8, minor=3: APT=-4, AMOD=-20, BMOD=12, size=(9<<6)|2.
Cases:
        dc.w $0b4a,$0059,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $0b4a,$0045,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $8b4a,$004d,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $8b4a,$005d,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $8b4a,$0055,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $8b4a,$0049,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $0b4a,$0041,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242
        dc.w $0b4a,$0051,$ffff,$ffff,-20,12,40,40,-4,$8000,$ffff,$0242

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

