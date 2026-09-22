; Minimal AmiScene Copper runtime usage.
; CopperBars must reside in Chip RAM in a real production.
        include "amiscene/ocs.i"

        xref    AmiCopperInstall
Start:
        lea     CopperBars(pc),a0
        bsr     AmiCopperInstall
.loop:
        bra.s   .loop

CopperBars:
        dc.w    $2c01,$7ffe
        dc.w    $0180,$0003
        dc.w    $6401,$7ffe
        dc.w    $0180,$000f
        dc.w    $ffff,$fffe
