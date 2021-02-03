SECTION "RAM", WRAM0

randomRegister::
	ds $1

ppuNotFunctional::
	ds $1

renderingHead::
	ds $2


SECTION "OAM", WRAMX[$DE00]
oamSrc::
	ds $A0

stackMax::
	ds $E000 - stackMax