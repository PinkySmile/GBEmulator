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
	reg INTERRUPT_ENABLED, VBLANK_INTERRUPT

	call waitVBLANK

	reset LCD_CONTROL

	xor a
	ld bc, $2000
	ld de, $C000
	call fillMemory

	ret