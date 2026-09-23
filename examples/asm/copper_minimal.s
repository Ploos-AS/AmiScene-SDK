; AmiScene M2 A500/OCS Copper reference
; 68000, OCS, PAL. No AmigaOS calls.
; NOTE: a production takeover must own the machine and restore system state.
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

; Visible proof: COLOR00 changes down the PAL frame.
.loop:
        btst    #6,$bfe001          ; CIAA PRA / left mouse button
        bne.s   .loop

        bsr     AmiCopperStop
        move.w  SavedDma(pc),d0
        bsr     AmiDmaRestore
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
