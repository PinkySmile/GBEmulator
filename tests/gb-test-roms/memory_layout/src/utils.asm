; Copies a chunk of memory into another
; Params:
;    bc -> The length of the chunk to copy
;    de -> The destination address
;    hl -> The source address
; Return:
;    None
; Registers:
;    af -> Not preserved
;    bc -> Not preserved
;    de -> Not preserved
;    hl -> Not preserved
copyMemory::
	xor a ; Check if size is 0
	or b
	or c
	ret z

	; Copy a byte of memory from hl to de
	ld a, [hli]
	ld [de], a
	inc de
	dec bc
	jr copyMemory ; Recurse until bc is 0

; Generates a pseudo random number.
; Params:
;    None
; Return:
;    a -> The number generated
; Registers:
;    af -> Not preserved
;    bc -> Preserved
;    de -> Preserved
;    hl -> Preserved
random::
	push hl

	ld a, [randomRegister]
	ld hl, divReg
	add a, [hl]
	ld [randomRegister], a

	pop hl
	ret

; Fill a chunk of memory with a single value
; Params:
;    a  -> Value to fill
;    bc -> The length of the chunk to fill
;    de -> The destination address
; Return:
;    None
; Registers:
;    af -> Not preserved
;    bc -> Not preserved
;    de -> Not preserved
;    hl -> Preserved
fillMemory::
	push af ; Save a
	xor a   ; Check if bc is 0
	or b
	or c
	jr z, .return
	pop af

	; Load a into de
	ld [de], a
	inc de
	dec bc
	jr fillMemory ; Recurse intil bc is 0
.return: ; End of recursion
	pop af
	ret

; Wait for VBLANK. Only returns when a VBLANK occurs.
; Params:
;    None
; Return:
;    None
; Registers:
;    af -> Not preserved
;    bc -> Not preserved
;    de -> Preserved
;    hl -> Preserved
waitVBLANK::
	ld a, [ppuNotFunctional]
	or a
	ret nz

	ld bc, $4000
.loop:
	ld a, [lcdLine]
	cp $90
	ret nc
	ld a, [lcdCtrl] ; Check if LCD is disabled
	bit 7, a
	ret z
	dec c
	jr nz, .loop
	dec b
	jr nz, .loop
	reg ppuNotFunctional, 1
	ret


; Uncompress compressed data
; Params:
;    a  -> Compression mode
;    hl -> Pointer to the compressed data
;    de -> Destination address
;    bc -> Data size
; Return:
;    None
; Registers:
;    af -> Not preserved
;    bc -> Not preserved
;    de -> Not preserved
;    hl -> Not preserved
uncompress::
	push af
	push de
	ld d, h
	ld e, l
	pop hl
	push hl
	ld hl, .case0
	rla
	rla
	rla
	add a, l
	ld l, a
	ld a, h
	adc $00
	ld h, a
	jp hl
.case0:
	pop hl
	ld a, [de]
	ld [hli], a
	ld [hli], a
	jr .endCase
	nop
	nop
.case1:
	pop hl
	xor a
	ld [hli], a
	ld a, [de]
	cpl
	ld [hli], a
	jr .endCase
.endCase:

	inc de
	dec bc
	xor a
	or b
	or c
	jr nz, .continue
	pop af
	push hl
	ld h, d
	ld l, e
	pop de
	ret
.continue:
	pop af
	push hl
	ld h, d
	ld l, e
	pop de
	jr uncompress

putchar::
	push af
	cp "\n"
	jr nz, .normal

	ld hl, renderingHead
	ld a, [hli]
	ld h, [hl]
	or $1F
	ld l, a
	push hl
	inc hl
	ld a, h
	and $9B
	ld h, a
	jr .checkAndScroll

.normal::
	ld hl, renderingHead
	ld a, [hli]
	ld h, [hl]
	ld l, a
	and $1F
	cp 20
	jr c, .draw
.newLine::
	ld a, $1F
	or l
	add 1
	ld l, a
	ld a, h
	adc $0
	and $9B
	ld h, a
	push hl
.checkAndScroll::
	call waitVBLANK
	ld a, [lcdLine]
	cp $9E
	jr c, .ok
.notOk::
	ld a, [lcdLine]
	cp $90
	jr nz, .notOk
.ok::
	ld a, 0
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	ld [hli], a
	pop hl
	ld a, [bgScrollY]
	add 8
	ld [bgScrollY], a
.draw::
	call waitVBLANK
	pop af
	ld [hli], a
	ld [$FF01], a
	ld a, $81
	ld [$FF02], a
	ld a, l
	ld [renderingHead], a
	ld a, h
	and $9B
	ld [renderingHead + 1], a
	ret


displayText::
	ld a, [hli]
	or a
	ret z
	push hl
	call putchar
	pop hl
	jr displayText

; Displays the failure message and locks the CPU
; Params:
;       c -> Dividande
;	d -> Diviseur
; Return:
;	e -> Reste
;       b -> Quotient
; Registers:
;	N/A
devide::
	ld b, 0
	ld e, b
	ld a, 8
.loop::
	push af
	sla b
	rl c
	rl e
	ld a, e
	cp d
	jr c, .noInc

	inc b
	sub d
	ld e, a

.noInc::
	pop af
	dec a
	jr nz, .loop
	ret

base::
	db "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0

displayDec::
	ld hl, base
	ld d, 10
	jp displayBase.noInitD

displayHex::
	cp $10
	jr nc, .allGood
	push af
	ld a, [base]
	call putchar
	pop af
.allGood::
	ld hl, base
	ld d, 16
	jp displayBase.noInitD

myStrLen::
	ld a, [hli]
	ret z
	call myStrLen
	inc a
	ret

displayBase::
	push af
	push hl
	call myStrLen
	ld d, a
	pop hl
	pop af
.noInitD::
	ld c, a
.recurse::
	call devide
	ld c, b
	xor a
	or b
	push bc
	ld c, e
	ld b, 0
	push hl
	add hl, bc
	ld a, [hl]
	pop hl
	pop bc
	push af
	call nz, .recurse
	pop af
	jp putchar