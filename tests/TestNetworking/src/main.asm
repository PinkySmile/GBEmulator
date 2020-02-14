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

; Tests if the current hardware is SGB
; Params:
;    None
; Return:
;    a      -> 0 if on DMG. 1 if on SGB.
;    Flag Z -> 1 if on DMG. 0 if on SGB.
; Registers:
;    af -> Not preserved
;    bc -> Not preserved
;    de -> Not preserved
;    hl -> Not preserved
testSGB::
	ld a, MLT_REQ
	ld hl, MLT_REQ_PAR
	call sendSGBCommand
	ld hl, JOYPAD_REGISTER
	ld b, [hl]
	ld [hl], %11100000
	ld [hl], %11010000
	ld [hl], %11110000
	ld a, [hl]
	xor b
	ret

; The text displayed when playing on a Gameboy
toSendText::
	db "To send-", 0, 0
bufferText:
	db "Buffer -", 0, 0
modeText:
	db "Mode-"
falseText:
	db "False"
trueText:
	db "True", 0
internalText:
	db "Internal"
externalText:
	db "External"
transferText:
	db "Is transfering-"
interruptText:
	db "Got interrupt-"

updateText::
	ld a, [TO_SEND_REGISTER]
	ld de, $9808
	call my_put_nbr

	ld a, [$FF01]
	ld de, $9828
	call my_put_nbr

	ld a, [$FF02]
	bit 0, a
	ld de, $9845
	ld bc, $8
	jr nz, .internal

	ld hl, externalText
	jr .end
.internal:
	ld hl, internalText
.end:
	call copyMemory

	ld a, [$FF02]
	bit 7, a
	ld de, $986F
	ld bc, $5
	jr z, .noTransfer

	ld hl, trueText
	jr .end2
.noTransfer:
	ld hl, falseText
.end2:
	call copyMemory


	ld a, [INTERUPT_OCCURED]
	ld de, $988E
	ld bc, $5
	or a
	jr z, .noInterrupt

	ld hl, trueText
	jr .end3
.noInterrupt:
	ld hl, falseText
.end3:
	call copyMemory
	ret

; Main function
main::
	call init               ; Init
	ld sp, $E000            ; Init stack
	call loadTextAsset

	ld hl, toSendText
	ld bc, bufferText - toSendText
	ld de, $9800
	call copyMemory

	ld bc, modeText - bufferText
	ld de, $9820
	call copyMemory

	ld bc, falseText - modeText
	ld de, $9840
	call copyMemory

	ld hl, transferText
	ld bc, interruptText - transferText
	ld de, $9860
	call copyMemory

	ld bc, interruptText - transferText
	ld de, $9880
	call copyMemory

	reg LCD_CONTROL, %10010001
.loop:
	halt
	call updateText
	call getKeys

	ld hl, TO_SEND_REGISTER
	bit 3, a
	call z, .dec
	bit 2, a
	call z, .inc

	ld hl, $FF02
	bit 5, a
	call z, .switch
	bit 4, a
	call z, .send

	jr .loop

.switch:
	bit 0, [hl]
	jr z, .isExternal
	res 0, [hl]
	jr .endSwitch
.isExternal:
	set 0, [hl]
.endSwitch:
	ret

.dec:
	dec [hl]
	ret

.inc:
	inc [hl]
	ret

.send:
	bit 7, [hl]
	ret nz

	ld a, [TO_SEND_REGISTER]
	ld [$FF01], a
	reset INTERUPT_OCCURED
	set 7, [hl]
	ret

include "src/init.asm"
include "src/fatal_error.asm"
include "src/utils.asm"
include "src/sgb_utils.asm"
include "src/interrupts.asm"