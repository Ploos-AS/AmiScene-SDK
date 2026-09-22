; AmiScene OCS/68000 Copper runtime
; Small independent routines; no OS dependency.
        include "amiscene/ocs.i"

; AmiCopperInstall
; In: a0 = Chip RAM Copper list
; Clobbers: d0/a1
; Writes COP1LC only. Does not alter DMA state.
AmiCopperInstall:
        lea     CUSTOM,a1
        move.l  a0,d0
        swap    d0
        move.w  d0,COP1LCH(a1)
        swap    d0
        move.w  d0,COP1LCL(a1)
        rts

; AmiCopperStart
; Clobbers: a1
; Restarts COP1 and enables master+Copper DMA.
AmiCopperStart:
        lea     CUSTOM,a1
        move.w  #0,COPJMP1(a1)
        move.w  #DMAF_SETCLR|DMAF_MASTER|DMAF_COPPER,DMACON(a1)
        rts

; AmiCopperStop
; Clobbers: a1
; Clears Copper DMA only. Master DMA is intentionally left alone.
AmiCopperStop:
        lea     CUSTOM,a1
        move.w  #DMAF_COPPER,DMACON(a1)
        rts

; AmiDmaSave
; Out: d0.w = readable DMA enable-state bits.
; Clobbers: a1
AmiDmaSave:
        lea     CUSTOM,a1
        move.w  DMACONR(a1),d0
        and.w   #DMAF_MASK,d0
        rts

; AmiDmaRestore
; In: d0.w = enable-state bits previously returned by AmiDmaSave.
; Clobbers: d1/a1
; First clears all writable DMA bits, then restores the saved enabled set.
AmiDmaRestore:
        lea     CUSTOM,a1
        move.w  d0,d1
        and.w   #DMAF_MASK,d1
        move.w  #DMAF_MASK,DMACON(a1)
        or.w    #DMAF_SETCLR,d1
        move.w  d1,DMACON(a1)
        rts
