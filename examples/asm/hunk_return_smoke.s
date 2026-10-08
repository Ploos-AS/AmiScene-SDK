; Minimal AmigaDOS Hunk guest-execution control.
; No Exec allocation, CUSTOM access, or Blitter dependency.
; A return code of zero proves the Hunk entrypoint ran and returned.
Start:
        moveq #0,d0
        rts
