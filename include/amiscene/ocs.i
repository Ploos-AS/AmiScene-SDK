; AmiScene OCS custom-chip register subset
CUSTOM      equ $dff000
COP1LCH     equ $080
COP1LCL     equ $082
COPJMP1     equ $088
DMACONR     equ $002
DMACON      equ $096
DMAF_SETCLR equ $8000
DMAF_MASTER equ $0200
DMAF_COPPER equ $0080
DMAF_MASK   equ $07ff

; Blitter
BLTCON0     equ $040
BLTCON1     equ $042
BLTAFWM     equ $044
BLTALWM     equ $046
BLTCPTH     equ $048
BLTCPTL     equ $04a
BLTBPTH     equ $04c
BLTBPTL     equ $04e
BLTAPTH     equ $050
BLTAPTL     equ $052
BLTDPTH     equ $054
BLTDPTL     equ $056
BLTSIZE     equ $058
BLTCMOD     equ $060
BLTBMOD     equ $062
BLTAMOD     equ $064
BLTDMOD     equ $066
DMAF_BLITTER equ $0040
