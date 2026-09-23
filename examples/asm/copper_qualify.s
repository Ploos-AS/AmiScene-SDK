; AmiScene M2 automated A500/OCS Copper qualification payload
; 68000, OCS, PAL. Runs a bounded raster interval and returns 0.
; This is CI evidence plumbing; copper_minimal.s remains the interactive reference.
        include "amiscene/ocs.i"

        xref    AmiCopperInstall
        xref    AmiCopperStart
        xref    AmiCopperStop
        xref    AmiDmaSave
        xref    AmiDmaRestore

Start:
        bsr     AmiDmaSave
        move.w  d0,SavedDma

        lea     CopperBars(pc),a0
        bsr     AmiCopperInstall
        bsr     AmiCopperStart

; Observe multiple PAL frames without OS calls. VPOSR bit 0 of the high byte
; changes across the 256-line boundary; count 16 transitions for a bounded run.
        lea     CUSTOM,a1
        moveq   #15,d1
.wait_hi:
        move.w  $004(a1),d0         ; VPOSR
        btst    #0,d0
        beq.s   .wait_hi
.wait_lo:
        move.w  $004(a1),d0
        btst    #0,d0
        bne.s   .wait_lo
        dbf     d1,.wait_hi

        bsr     AmiCopperStop
        move.w  SavedDma(pc),d0
        bsr     AmiDmaRestore
        moveq   #0,d0
        rts

        even
SavedDma:
        dc.w    0

        cnop    0,4
CopperBars:
        dc.w    $2c01,$fffe
        dc.w    $0180,$0003
        dc.w    $5001,$fffe
        dc.w    $0180,$0006
        dc.w    $7801,$fffe
        dc.w    $0180,$000f
        dc.w    $a001,$fffe
        dc.w    $0180,$0006
        dc.w    $c801,$fffe
        dc.w    $0180,$0003
        dc.w    $ffff,$fffe
CopperBars_end:
