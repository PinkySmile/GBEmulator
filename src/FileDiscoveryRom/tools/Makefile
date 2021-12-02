ifdef OS
   NAME = compressor.exe
else
   NAME = compressor
endif

SRC =	compressor.c

OBJ =	$(SRC:%.c=%.o)

INC =

LDFLAGS =

CFLAGS= $(INC)	\
		-W		\
		-Wall	\
		-Wextra	\

CC =	gcc

LIBS =

all:	$(LIBS) $(NAME)

$(NAME):$(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean:	clean
	$(RM) $(NAME)

ffclean:fclean

re:	fclean all

dbg:	CFLAGS += -g -O0
dbg:	ffclean all
