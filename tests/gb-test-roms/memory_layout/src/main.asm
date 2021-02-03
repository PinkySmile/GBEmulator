include "constants.asm"
include "macro.asm"
include "registers.asm"

SECTION "Main", ROM0

; Locks the CPU
; Params:
;	None
; Return:
;	None
; Registers:
;	N/A
lockup::
	reset interruptFlag
	ld [interruptEnable], a
.loop:
	halt
	jr .loop

failed::
	db "\n\nFailed #",0

passed::
	db "\nPassed\n", 0

; Main function
main::
	ld sp, $FFFF
	call init

	xor a
	ld de, vramStart + " " * $10
	ld bc, fontsEnd - fonts
	ld hl, fonts
	call uncompress

	reg renderingHead + 1, vramBgStart >> 8
	reg bgScrollY, -17 * $8
	reg lcdCtrl, $91

	ld hl, testName
	call displayText
	ld a, "\n"
	call putchar
	ld a, "\n"
	call putchar

	call tests

	ld hl, passed
	call displayText
	jp lockup

echoRam1::
	db "\nWriting to WRAM\ndoesn't reflect in\necho RAM", 0

echoRam2::
	db "\nWriting to echo\nRAM doesn't reflect\nin WRAM", 0

testName::
	db "Memory layout", 0
tests::
	ld de, oamRamTest2
	push de
oamRamTest1::
	ld hl, $E000
	ld de, $C000
	ld bc, $0400
.loop::
	ld a, [de]
	cp [hl]
	call nz, OAMfailed
	inc de
	inc hl
	dec b
	jr nz, .loop
.loopTrashRamLoop::
	call random
	ld [de], a
	cp [hl]
	call nz, OAMfailed
	inc de
	inc hl
	ld a, h
	cp $FE
	jr nz, .loopTrashRamLoop
	ld a, c
	or a
	ret z

	ld b, h
	ld c, l
	ld hl, displayECHORamMsg1
	ld a, 1
	jp failedTest

oamRamTest2::
	ld hl, $C000
	ld de, $E000
	ld bc, $0400
.loop::
	ld a, [de]
	cp [hl]
	call nz, OAMfailed
	inc de
	inc hl
	dec b
	jr nz, .loop
.loopTrashRamLoop::
	call random
	ld [de], a
	cp [hl]
	call nz, OAMfailed
	inc de
	inc hl
	ld a, h
	cp $DE
	jr nz, .loopTrashRamLoop
	ld a, c
	or a
	ret z

	ld b, h
	ld c, l
	ld hl, displayECHORamMsg2
	ld a, 1
	jp failedTest

OAMfailed::
	push bc
	push de
	push hl
	ld a, "$"
	call putchar

	pop hl
	push hl
	ld a, h
	call displayHex
	pop hl
	push hl
	ld a, l
	call displayHex

	ld a, "<"
	call putchar
	ld a, "-"
	call putchar
	ld a, ">"
	call putchar
	ld a, "$"
	call putchar

	pop hl
	pop de
	push de
	push hl
	ld a, d
	call displayHex
	pop hl
	pop de
	push de
	push hl
	ld a, e
	call displayHex

	ld a, " "
	call putchar

	pop hl
	push hl
	ld a, [hl]
	call displayHex

	ld a, ":"
	call putchar

	pop hl
	pop de
	push de
	push hl
	ld a, [de]
	call displayHex

	ld a, "\n"
	call putchar

	pop hl
	pop de
	pop bc
	ld c, 1
	ret


displayECHORamMsg1::
	ld hl, echoRam1
	jp displayText

displayECHORamMsg2::
	ld hl, echoRam2
	jp displayText


; Displays the failure message and locks the CPU
; Params:
;       a  -> Test that failed
;	hl -> Function to print reason of test failure
; Return:
;	None
; Registers:
;	N/A
failedTest::
	push af
	push de
	ld a, b
	ld [$FFFE], a
	ld a, c
	ld [$FFFD], a
	ld bc, .returnPoint
	push bc
	ld a, [$FFFE]
	ld b, a
	ld a, [$FFFD]
	ld c, a
	jp hl
.returnPoint::

	ld hl, failed
	call displayText
	pop de
	pop af
	ld c, a
	call displayDec

	ld a, "\n"
	call putchar

	jp lockup

include "init.asm"
include "interrupts.asm"
include "utils.asm"