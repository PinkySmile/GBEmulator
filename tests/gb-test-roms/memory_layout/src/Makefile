NAME = memory_layout

EXT = gb

ASM = rgbasm

LD = rgblink

FIX = rgbfix

FIXFLAGS = -cjsv -k 01 -l 0x33 -m 0x00 -p 0 -r 00 -t "`echo "$(NAME)" | tr a-z A-Z | tr "_" " "`"

ASMFLAGS =

LDFLAGS = -n $(NAME).sym -l $(NAME).link

FXFLAGS = -u

FX = rgbgfx

SRCS = \
	main.asm \
	mem_layout.asm \
	assets.asm \
	text.asm \
	wram.asm


IMGS = \

COLORED_IMGS = \


OBJS = $(SRCS:%.asm=%.o)

COLORED_IMGS_FX = $(COLORED_IMGS:%.png=%.cfx)

PALS = $(COLORED_IMGS:%.png=%.pal)

MAPS = $(IMGS:%.png=%.tilemap) $(COLORED_IMGS:%.png=%.tilemap)

all:	$(NAME).$(EXT)

run:	re
	wine "$(BGB_PATH)" ./$(NAME).$(EXT)

runw:	re
	"$(BGB_PATH)" ./$(NAME).$(EXT)

%.fx : %.png
	$(FX) $(FXFLAGS) -T -o $@ $<

%.cfx : %.png
	$(FX) $(FXFLAGS) -T -P -o $@ $<

%.o : %.asm
	$(ASM) -o $@ $(ASMFLAGS) $<

$(NAME).$(EXT): $(COLORED_IMGS_FX) $(IMGSFX) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	$(FIX) $(FIXFLAGS) $@

clean:
	$(RM) $(OBJS) $(IMGSFX) $(COLORED_IMGS_FX) $(MAPS) $(PALS)

fclean:	clean
	$(RM) $(NAME).$(EXT)

re:	fclean all
