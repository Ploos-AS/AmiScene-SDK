; AmiScene OCS Blitter helpers
; a0 = descriptor, a1/a2/a3/a4 = A/B/C/D pointers.
; Descriptor words: BLTCON0, BLTCON1, AFWM, ALWM, AMOD, BMOD, CMOD, DMOD, SIZE.
; Caller owns Chip RAM placement and waits/interrupt policy.

        include "../../../include/amiscene/ocs.i"

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
