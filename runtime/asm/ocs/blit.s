; AmiScene OCS Blitter helpers
; a0 = descriptor, a1/a2/a3/a4 = A/B/C/D pointers.
; Descriptor words: BLTCON0, BLTCON1, AFWM, ALWM, AMOD, BMOD, CMOD, DMOD, SIZE.
; Caller owns Chip RAM placement and waits/interrupt policy.

        include "../../../include/amiscene/ocs.i"

        xdef    AmiBlitWait
        xdef    AmiBlitStart
        xdef    AmiBlitLineStart

AmiBlitWait:
.wait:  btst    #6,DMACONR(a6)
        bne.s   .wait
        rts

AmiBlitStart:
        bsr.s   AmiBlitWait
        move.w  (a0)+,BLTCON0(a6)
        move.w  (a0)+,BLTCON1(a6)
        move.w  (a0)+,BLTAFWM(a6)
        move.w  (a0)+,BLTALWM(a6)
        move.w  (a0)+,BLTAMOD(a6)
        move.w  (a0)+,BLTBMOD(a6)
        move.w  (a0)+,BLTCMOD(a6)
        move.w  (a0)+,BLTDMOD(a6)
        move.l  a1,BLTAPTH(a6)
        move.l  a2,BLTBPTH(a6)
        move.l  a3,BLTCPTH(a6)
        move.l  a4,BLTDPTH(a6)
        move.w  (a0),BLTSIZE(a6)
        rts

; AmiBlitLineStart
; a0 -> line descriptor words:
; BLTCON0 (A+C+D; B texture is preloaded), BLTCON1, BLTAFWM, BLTALWM, BLTAMOD, BLTBMOD,
; BLTCMOD, BLTDMOD, A error term, ADAT, BDAT, BLTSIZE.
; a3 = C bitmap pointer, a4 = D bitmap pointer, a6 = CUSTOM.
AmiBlitLineStart:
        bsr     AmiBlitWait
        move.w  (a0)+,BLTCON0(a6)
        move.w  (a0)+,BLTCON1(a6)
        move.w  (a0)+,BLTAFWM(a6)
        move.w  (a0)+,BLTALWM(a6)
        move.w  (a0)+,BLTAMOD(a6)
        move.w  (a0)+,BLTBMOD(a6)
        move.w  (a0)+,BLTCMOD(a6)
        move.w  (a0)+,BLTDMOD(a6)
        ; In line mode BLTAPT is the signed error accumulator.  Program
        ; the full longword as documented by the HRM/reference examples.
        move.w  (a0)+,d0
        ext.l   d0
        move.l  d0,BLTAPTH(a6)
        move.w  (a0)+,BLTADAT(a6)
        move.w  (a0)+,BLTBDAT(a6)
        move.l  a3,BLTCPTH(a6)
        move.l  a4,BLTDPTH(a6)
        move.w  (a0),BLTSIZE(a6)
        rts
