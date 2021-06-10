EntryPointCode::
LOAD "DMA", HRAM
EntryPoint::
	ld a, [selectedEntryType]
	cp TYPE_SYMLINK
	ret z ;Let's not follow symlinks
	ld [useSelectedItem], a
	jp $100
ENDL
EntryPointCodeEnd::

monochromePal::
	dw $7FFF, $2108, $4210, $0000
selectedPal::
	dw $7C00, $2108, $4210, $7FFF

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
	pop de
	ld sp, $FFFF
	push de
	reg INTERRUPT_ENABLED, VBLANK_INTERRUPT

	call waitVBLANK

	reset LCD_CONTROL

	xor a
	ld bc, $2000
	ld de, $C000
	call fillMemory

	ld hl, EntryPointCode
	ld bc, EntryPointCodeEnd - EntryPointCode
	ld de, EntryPoint
	call copyMemory

	ld hl, fontSprite
	ld de, $8000
	ld bc, fileTypeSprites - fontSprite
	call uncompress
	ld bc, assetsEnd - fileTypeSprites
	call uncompress

	ld hl, cgbBgPalIndex
	ld a, $80
	ld [hli], a
	ld de, monochromePal
	ld b, $10
.bgPalLoop::
	ld a, [de]
	inc de
	ld [hl], a
	dec b
	jr nz, .bgPalLoop

	ret