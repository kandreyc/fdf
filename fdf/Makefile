#[----PROJECT NAME----]#
NAME		=	fdf

#[----PATH TO HEADERS----]#
FDF_H		=	./includes/

#[---COMPILE---]#
ACT			=	gcc
FLAGS		=	-Wall -Wextra -Werror

#[----ATTACH THE HEADERS----]#
GCC_MLX_H	=	-lmlx -framework OpenGL -framework AppKit
GCC_FDF_H	=	-I $(FDF_H)
GCC_ALL_H	=	$(GCC_FDF_H) $(GCC_MLX_H)

#[----FDF SOURCES----]#
SRC_FDF_C		=	./functions/main.c					\
					./functions/reading.c				\
					./functions/session.c				\
					./functions/straight.c				\
					./functions/rendering.c				\
					./functions/control.c				\
					./functions/help/strsplit.c			\
					./functions/error.c

SRC_FDF_O		=	./functions/main.o					\
					./functions/reading.o				\
					./functions/session.o				\
					./functions/straight.o				\
					./functions/rendering.o				\
					./functions/control.o				\
					./functions/help/strsplit.o			\
					./functions/error.o


#[----COLORS]----#
GREEN			=	\033[32m
DEFAULT			=	\033[39m


all: $(NAME)

$(NAME): $(SRC_FDF_O)
	@ $(ACT) $(FLAGS) $(GCC_ALL_H) $(SRC_FDF_O) -o $(NAME)
	@ echo "$(GREEN)[fdf]$(DEFAULT)"

%.o : %.c $(FDF_H)
	@ $(ACT) $(FLAGS) -c -o $@ $<

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC_FDF_C) $(FDF_H)fdf.h
	@ echo "$(GREEN)[norminette]"

clean:
	@ rm -f $(SRC_FDF_O)
	@ echo "$(GREEN)[clean]$(DEFAULT)"

fclean: clean
	@ rm -f $(NAME)
	@ echo "$(GREEN)[fclean]$(DEFAULT)"

test1:
	@ ./fdf maps/julia.fdf maps/elem-fract.fdf maps/t1.fdf maps/t2.fdf maps/mars.fdf maps/pyramide.fdf maps/42.fdf

test2:
	@ ./fdf maps/10-2.fdf maps/10-70.fdf maps/20-60.fdf maps/50-4.fdf maps/100-6.fdf maps/elem-col.fdf maps/elem.fdf maps/elem2.fdf

test3:
	@ ./fdf maps/basictest.fdf maps/pentenegpos.fdf maps/plat.fdf maps/pnp_flat.fdf maps/pyra.fdf

re: fclean all