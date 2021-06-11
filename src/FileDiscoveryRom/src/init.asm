EntryCodePattern1::
	db $00, $00, $00, $00, $F0, $FC, $FC, $F3
	db $3C, $3C, $3C, $3C, $F0, $F0, $00, $F3
	db $00, $00, $00, $CF, $00, $0F, $3F, $0F
	db $00, $00, $C0, $0F, $00, $00, $00, $F0
	db $00, $00, $00, $F3, $00, $00, $00, $C0
	db $03, $03, $03, $FF, $C0, $C0, $C0, $C3
	db $00, $00, $00, $FC, $F3, $F0, $F0, $F0
	db $3C, $FC, $FC, $3C, $F3, $F3, $F3, $F3
	db $F3, $C3, $C3, $C3, $CF, $CF, $CF, $CF
	db $3C, $3F, $3C, $0F, $3C, $FC, $00, $FC
	db $FC, $F0, $F0, $F0, $F3, $F3, $F3, $F0
	db $C3, $C3, $C3, $FF, $CF, $CF, $CF, $C3
	db $0F, $0F, $0F, $FC
EntryCodePattern2::
	db $3C, $42, $B9, $A5, $B9, $A5, $42, $3C

EntryPointCode::
LOAD "DMA", WRAMX
EntryPoint::
	ld a, [selectedEntryType]
	cp TYPE_SYMLINK
	ret z ;Let's not follow symlinks
	cp TYPE_DIRECTORY
	jr nz, .initGBState
	ld [useSelectedItem], a
	jp copyFolderFirstTime

.initGBState::
	ld sp, $FFFE
	reg dmgBgPalData, $FC
	call waitVBLANK
	reset lcdCtrl

	ld a, [BOOT_ROM_A_INIT]
	cp $11
	jr z, .cgb
	ld de, $01B0 ; af
	push de
	ld de, $0013 ; bc
	push de
	ld de, $00D8 ; de
	push de
	ld de, $014D ; hl
	push de
	jr .end
.cgb:
	reg VRAMBankSelect, 1
	xor a
	ld de, $8000
	ld bc, $2000
	call fillMemory
	ld [VRAMBankSelect], a
	ld de, $1180 ; af
	push de
	ld de, $0000 ; bc
	push de
	ld de, $FF56 ; de
	push de
	ld de, $000D ; hl
	push de

.end:
	xor a
	ld de, $8000
	ld bc, $2000
	call fillMemory

	ld a, $C
	ld hl, $990F
.loop1:
	ld [hld], a
	dec a
	jr nz, .loop1

	ld a, $18
	ld hl, $992F
.loop2:
	ld [hld], a
	dec a
	cp $C
	jr nz, .loop2

	reg $9910, $19

	ld c, 88
	ld de, EntryCodePattern1
	ld hl, $8000
.pattern1Loop:
	ld a, [de]
	ld [hli], a
	inc hl
	ld [hli], a
	inc hl
	inc de
	dec c
	jr nz, .pattern1Loop

	ld c, 8
.pattern2Loop:
	ld a, [de]
	ld [hli], a
	inc hl
	inc de
	dec c
	jr nz, .pattern2Loop

	reset bgScrollY
	reg lcdCtrl, $91
	call waitVBLANK
	pop hl
	pop de
	pop bc
	pop af
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
	ld h, a

	pop de
	ld sp, $FFFF
	push de
	reg INTERRUPT_ENABLED, VBLANK_INTERRUPT

	call waitVBLANK
	reset LCD_CONTROL

	ld bc, $2000
	ld de, $C000
	call fillMemory

	ld a, h
	ld [BOOT_ROM_A_INIT], a

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