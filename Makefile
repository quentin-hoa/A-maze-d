##
## EPITECH PROJECT, 2026
## Module_name, project_name
## File description:
## Makefile
##

NAME	=		project_name

CFLAGS	= 		-W -Wall -Wextra

SRC		=		./src/main.c \
	./lib/my_printf/src/my_0.c \
	./lib/my_printf/src/my_c.c \
	./lib/my_printf/src/my_d.c \
	./lib/my_printf/src/my_e.c \
	./lib/my_printf/src/my_ee.c \
	./lib/my_printf/src/my_f.c \
	./lib/my_printf/src/my_g.c \
	./lib/my_printf/src/my_o.c \
	./lib/my_printf/src/my_p.c \
	./lib/my_printf/src/my_plus.c \
	./lib/my_printf/src/my_printf_core.c \
	./lib/my_printf/src/my_put_decimal.c \
	./lib/my_printf/src/my_s.c \
	./lib/my_printf/src/my_space.c \
	./lib/my_printf/src/my_u.c \
	./lib/my_printf/src/my_w.c \
	./lib/my_printf/src/my_x.c \
	./lib/my_printf/src/my_xx.c \
	./lib/other_functions/my_array_len.c \
	./lib/other_functions/my_atoi.c \
	./lib/other_functions/my_evil_str.c \
	./lib/other_functions/my_getnbr.c \
	./lib/other_functions/my_isdigit.c \
	./lib/other_functions/my_isneg.c \
	./lib/other_functions/my_print_word_count.c \
	./lib/other_functions/my_put_nbr.c \
	./lib/other_functions/my_revstr.c \
	./lib/other_functions/my_showmem.c \
	./lib/other_functions/my_showstr.c \
	./lib/other_functions/my_sort_int_array.c \
	./lib/other_functions/my_strcapitalize.c \
	./lib/other_functions/my_strcat.c \
	./lib/other_functions/my_strchr.c \
	./lib/other_functions/my_strcmp.c \
	./lib/other_functions/my_str_contains.c \
	./lib/other_functions/my_str_count_char.c \
	./lib/other_functions/my_str_count_word.c \
	./lib/other_functions/my_strcpy.c \
	./lib/other_functions/my_strdup.c \
	./lib/other_functions/my_str_isalnum.c \
	./lib/other_functions/my_str_isalpha.c \
	./lib/other_functions/my_str_islower.c \
	./lib/other_functions/my_str_isnum.c \
	./lib/other_functions/my_str_isupper.c \
	./lib/other_functions/my_strjoin.c \
	./lib/other_functions/my_strlen.c \
	./lib/other_functions/my_strlowcase.c \
	./lib/other_functions/my_strncat.c \
	./lib/other_functions/my_strncmp.c \
	./lib/other_functions/my_strncpy.c \
	./lib/other_functions/my_strrchr.c \
	./lib/other_functions/my_str_replace.c \
	./lib/other_functions/my_strstr.c \
	./lib/other_functions/my_strtrim.c \
	./lib/other_functions/my_strupcase.c \
	./lib/other_functions/my_swap.c \
	./lib/other_functions/print_only_alpha.c

OBJ		=		$(SRC:.c=.o)

CSFML	=		-lcsfml-graphics -lcsfml-system -lcsfml-audio \
	-lcsfml-window -lm

all:	$(OBJ)
		clang $(OBJ) -o $(NAME) -I./include $(CFLAGS) $(CSFML)

clean:
		rm -f $(OBJ)

fclean:	clean
		rm -f $(NAME)

re:		fclean all

debug:	CFLAGS+= -g
debug:	all
