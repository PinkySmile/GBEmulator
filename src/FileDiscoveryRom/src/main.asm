include "src/constants.asm"
include "src/macro.asm"
include "src/registers.asm"

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

gb_ext::
	db ".gb", 0
gbc_ext::
	db ".gbc", 0
GB_ext::
	db ".GB", 0
GBC_ext::
	db ".GBC", 0
sav_ext::
	db ".sav", 0

; Params:
;    bc -> The max length of the chunk to copy
;    de -> The destination address
;    hl -> The source address
; Return:
;    None
; Registers:
;    af -> Not preserved
;    bc -> Not preserved
;    de -> Not preserved
;    hl -> Not preserved
strncpy::
	xor a ; Check if size is 0
	or b
	or c
	ret z

	; Copy a byte of memory from hl to de
	ld a, [hli]
	or a
	ret z

	ld [de], a
	inc de
	dec bc
	jp copyMemory ; Recurse until bc is 0


strlen_::
	ld b, $FF
.loop:
	inc b
	ld a, [hli]
	or a
	jr nz, .loop
	ld a, b
	ret

strrchr::
	call strlen_
	dec hl
	dec hl
.loop:
	ld a, [hl]
	cp c
	ret z
	dec hl
	dec b
	jr nz, .loop
	ld hl, $0000
	ret


strcmp_::
	ld a, [de]
	inc de
	or a
	ld c, a
	ld a, [hli]
	jr z, .end
	cp c
	jr z, strcmp_
.end:
	sub c
	ret


getFileType::
	ld a, [selectedEntryType]
	cp TYPE_FILE
	set 7, a
	ret nz

	ld hl, selectedEntryName
	ld c, "."
	call strrchr

	push hl
	ld de, gb_ext
	call strcmp_
	pop hl
	ld a, 136
	ret z

	push hl
	ld de, gbc_ext
	call strcmp_
	pop hl
	ld a, 136
	ret z

	push hl
	ld de, GB_ext
	call strcmp_
	pop hl
	ld a, 136
	ret z

	push hl
	ld de, GBC_ext
	call strcmp_
	pop hl
	ld a, 136
	ret z

	push hl
	ld de, sav_ext
	call strcmp_
	pop hl
	ld a, 137
	ret z
	ld a, 129
	ret


drawEntry::
	push hl
	call getFileType
	pop hl
	push af
	call waitVBLANK
	pop af
	ld [hli], a
	ld bc, 31
	ld d, h
	ld e, l
	ld hl, selectedEntryName
	jp strncpy

swapOnlyRom::
	ld hl, ONLY_ROM_BIT
	ld a, 1
	xor [hl]
	ld [hl], a
	ld [showOnlyRoms], a

copyFolderFirstTime::
	call waitVBLANK
	reset LCD_CONTROL

	reg VRAMBankSelect, 1
	xor a
	ld de, $9800
	ld bc, $300
	call fillMemory
	ld [VRAMBankSelect], a
	ld de, $9800
	ld bc, $300
	call fillMemory

	ld c, 18
	ld a, [numberOfEntries + 1]
	or a
	jr nz, .initPhase ; if (numberOfEntries >= 0x100)
	ld a, [numberOfEntries]
	cp c
	jr nc, .initPhase ; if (numberOfEntries >= 18)
	ld c, a
.initPhase:
	reg VRAMBankSelect, 1
	ld de, $9800
	push bc
	ld bc, 32
	call fillMemory
	pop bc
	ld hl, VRAM_SELECTED_ADDR + 1
	ld a, $98
	ld [hld], a
	xor a
	ld [hld], a
	ld [hld], a
	ld [currentlySelectedEntry + 1], a
	ld [VRAMBankSelect], a
	ld [bgScrollY], a
	ld a, c
	ld [hld], a
	or $FF
	ld [hld], a
	ld [hld], a
	xor a
	ld hl, $9800
.copyLoop:
	ld [currentlySelectedEntry], a
	push bc
	push af
	push hl
	call drawEntry
	pop hl
	pop af
	pop bc
	ld de, 32
	add hl, de
	inc a
	dec c
	jr nz, .copyLoop
	reset currentlySelectedEntry
	reg LCD_CONTROL, LCD_BASE_CONTROL
	ret

moveDown::
	ld hl, numberOfEntries
	ld a, [hli]
	ld c, a
	ld b, [hl]
	dec bc

	ld a, [currentlySelectedEntry]
	cp c
	jr nz, .allGood
	ld a, [currentlySelectedEntry + 1]
	cp b
	ret z
.allGood::
	ld hl, VRAM_SELECTED_ADDR
	ld a, [hli]
	ld h, [hl]
	ld l, a

	reg VRAMBankSelect, 1
	xor a
	REPT 32
	ld [hli], a
	ENDR
	ld [VRAMBankSelect], a
	res 2, h

	ld d, h
	ld e, l
	reg VRAMBankSelect, 1
	REPT 32
	ld [hli], a
	ENDR
	reset VRAMBankSelect

	ld a, e
	ld hl, VRAM_SELECTED_ADDR
	ld [hli], a
	ld [hl], d

	ld hl, currentlySelectedEntry
	ld a, [hl]
	add 1
	ld c, a
	ld [hli], a
	ld a, [hl]
	adc 0
	ld b, a
	ld [hli], a

	; if (*SELECT_ITEM_BOTTOM != bc) return;
	ld hl, SELECT_ITEM_BOTTOM
	ld a, [hli]
	cp c
	ret nz
	ld a, [hl]
	cp b
	ret nz

	inc bc
	ld a, b
	ld [hld], a
	ld [hl], c

	ld hl, SELECT_ITEM_TOP
	ld a, [hl]
	add 1
	ld c, a
	ld [hli], a
	ld a, [hl]
	adc 0
	ld b, a
	ld [hli], a

	ld h, d
	ld l, e
	call drawEntry

	ld hl, bgScrollY
	ld a, [hl]
	add 8
	ld [hl], a
      	ret

moveUp::
	ld a, [currentlySelectedEntry]
	or a
	jr nz, .allGood
	ld a, [currentlySelectedEntry + 1]
	or a
	ret z
.allGood::
	ld hl, VRAM_SELECTED_ADDR
	ld a, [hli]
	ld h, [hl]
	ld l, a

	ld d, h
	ld e, l
	reg VRAMBankSelect, 1
	xor a
	REPT 32
	ld [hli], a
	ENDR
	ld [VRAMBankSelect], a

	ld hl, -32
	add hl, de
	set 3, h
	res 2, h

	ld d, h
	ld e, l
	reg VRAMBankSelect, 1
	REPT 32
	ld [hli], a
	ENDR
	reset VRAMBankSelect

	ld a, e
	ld hl, VRAM_SELECTED_ADDR
	ld [hli], a
	ld [hl], d

	ld hl, currentlySelectedEntry
	ld a, [hl]
	sub 1
	ld c, a
	ld [hli], a
	ld a, [hl]
	sbc 0
	ld b, a
	ld [hli], a

	; if (*SELECT_ITEM_TOP != bc) return;
	ld hl, SELECT_ITEM_TOP
	ld a, [hli]
	cp c
	ret nz
	ld a, [hl]
	cp b
	ret nz

	dec bc
	ld a, b
	ld [hld], a
	ld [hl], c

	ld hl, SELECT_ITEM_BOTTOM
	ld a, [hl]
	sub 1
	ld c, a
	ld [hli], a
	ld a, [hl]
	sbc 0
	ld b, a
	ld [hli], a

	ld h, d
	ld l, e
	call drawEntry

	ld hl, bgScrollY
	ld a, [hl]
	sub 8
	ld [hl], a
      	ret

tryGoBack::
	ld hl, currentlySelectedEntry
	ld a, [hli]
	ld b, [hl]
	ld c, a
	xor a
	ld [hld], a
	ld [hl], a
	ld de, selectedEntryName
	ld a, [de]
	cp "."
	jr nz, .noGood

	inc e
	ld a, [de]
	cp "."
	jr nz, .noGood

	inc e
	ld a, [de]
	or a
	jp z, EntryPoint

.noGood::
	ld a, c
	ld [hli], a
	ld [hl], b
	ret

; Main function
main::
	call init               ; Init
	ld sp, $E000            ; Init stack
	call copyFolderFirstTime
.loop:
	halt
	reset interruptFlag
	call getKeys

upKeyHandler::
	push af
	bit UP_BIT, a
	jr nz, .nope
	ld de, .end
	push de
	ld hl, PRESS_UP_CTR
	ld a, [hl]
	inc [hl]
	or a
	jp z, moveUp
	bit 7, a
	jr nz, .allGood
	bit 6, a
	jr nz, .allGood
	bit 5, a
	ret z
.allGood:
	set 7, [hl]
	and 3
	jp z, moveUp
	ret
.nope:
	xor a
	ld [PRESS_UP_CTR], a
.end:
	pop af

downKeyHandler::
	push af
	bit DOWN_BIT, a
	jr nz, .nope
	ld de, .end
	push de
	ld hl, PRESS_DOWN_CTR
	ld a, [hl]
	inc [hl]
	or a
	jp z, moveDown
	bit 7, a
	jr nz, .allGood
	bit 6, a
	jr nz, .allGood
	bit 5, a
	ret z
.allGood:
	set 7, [hl]
	and 3
	jp z, moveDown
	ret
.nope:
	xor a
	ld [PRESS_DOWN_CTR], a
.end:
	pop af


	call getKeysFiltered
	push af
	bit A_BIT, a
	call z, EntryPoint
	pop af

	push af
	bit B_BIT, a
	call z, tryGoBack
	pop af

	bit SELECT_BIT, a
	call z, swapOnlyRom
	jr main.loop

include "src/init.asm"
include "src/utils.asm"
include "src/interrupts.asm"
include "src/assets.asm"
include "src/text.asm"