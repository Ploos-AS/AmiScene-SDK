; AmiScene OCS/68000 Copper runtime
; Input: a0 = chip-memory address of Copper list
; Clobbers: d0/a1
; Requirement: list and this caller's DMA policy are the coder's responsibility.
; This routine only installs COP1LC, strobes COPJMP1 and enables master+Copper DMA.

        include "amiscene/ocs.i"

AmiCopperInstall:
        lea     CUSTOM,a1
        move.l  a0,d0
        swap    d0
        move.w  d0,COP1LCH(a1)
        swap    d0
        move.w  d0,COP1LCL(a1)
        move.w  #0,COPJMP1(a1)
        move.w  #DMAF_SETCLR|DMAF_MASTER|DMAF_COPPER,DMACON(a1)
        rts
