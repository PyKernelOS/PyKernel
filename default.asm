[bits 32]           ; Set Bit Mode to 32

extern Startup
extern Update

global _start
_start:
    call Startup    ; Call Startup Function
    cli             ; Disable Interrupts
    jmp .loop       ; Call Update Function

.loop:
    call Update     ; Call Update Function
    cli             ; Clear Interrupts
    jmp .loop       ; Loop