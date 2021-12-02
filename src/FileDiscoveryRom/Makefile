NAME = file_discovery

ASM = rgbasm

LD = rgblink

FIX = rgbfix

FIXFLAGS = -jsvc -k 01 -l 0x33 -m 0xCE -p 0 -t FILE_DISCOVERY

ASMFLAGS =

LDFLAGS = -n $(NAME).sym -l $(NAME).link

FXFLAGS =

FX = rgbgfx

SRCS = \
	src/main.asm \
	src/mem_layout.asm

IMGS =

COMPRESSED_IMGS = \
	assets/font.png \
	assets/file_types.png

COMPRESSEDIMGSFX = $(COMPRESSED_IMGS:%.png=%.cfx)

IMGSFX = $(IMGS:%.png=%.fx)

OBJS = $(SRCS:%.asm=%.o)

ifdef OS
   COMPRESSOR_EXE = compressor.exe
   COMPRESSOR = tools\$(COMPRESSOR_EXE)
else
   COMPRESSOR_EXE = compressor
   COMPRESSOR = tools/$(COMPRESSOR_EXE)
endif

all:	$(COMPRESSOR) $(NAME).inl

$(COMPRESSOR):
	$(MAKE) -C tools $(COMPRESSOR_EXE)

run:	re
	wine "$(BGB_PATH)" ./$(NAME).gbc

runw:	re
	"$(BGB_PATH)" ./$(NAME).gbc

%.fx : %.png
	$(FX) $(FXFLAGS) -o $@ $<

%.cfx : %.png
	$(FX) $(FXFLAGS) -o $@ $<
	$(COMPRESSOR) $@

%.o : %.asm
	$(ASM) -o $@ $(ASMFLAGS) $<

$(NAME).inl: $(NAME).gbc
	python ./inliner.py $(NAME).gbc $@

$(NAME).gbc:	$(COMPRESSEDIMGSFX) $(IMGSFX) $(OBJS)
	$(LD) $(LDFLAGS) -o $@ $(OBJS)
	$(FIX) $(FIXFLAGS) $@

clean:
	$(MAKE) -C tools clean
	$(RM) $(OBJS) $(IMGSFX) $(COMPRESSEDIMGSFX)

fclean:	clean
	$(MAKE) -C tools fclean
	$(RM) $(NAME).gbc $(NAME).inl

re:	fclean all
