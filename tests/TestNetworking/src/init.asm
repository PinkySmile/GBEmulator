; Enable interupts and init RAM
; Params:
;    None
; Return:
;    None
; Registers:
;    af -> Preserved
;    bc -> Not preserved
;    de -> Not preserved
;    hl -> Not preserved
init::
	call waitVBLANK
	reset LCD_CONTROL
	ei
	reg INTERRUPT_ENABLED, SERIAL_INTERRUPT | VBLANK_INTERRUPT
	xor a
	ld bc, $2000
	ld de, $C000
	call fillMemory
	ld bc, $2000
	ld de, $8000
	call fillMemory
	ret
