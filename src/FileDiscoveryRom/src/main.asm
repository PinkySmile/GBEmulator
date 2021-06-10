include "src/constants.asm"
include "src/macro.asm"

SECTION "Main", ROM0

; Locks the CPU
; Params:
;    None
; Return:
;    None
; Registers:
;    N/A
lockup::
	reset INTERRUPT_ENABLED
	halt
	jr lockup

; Main function
main::
	call init               ; Init
	ld sp, $E000            ; Init stack
	jp lockup

include "src/init.asm"
include "src/utils.asm"
include "src/interrupts.asm"