#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/23 01:45:49 by mbiliaie          #+#    #+#              #
#    Updated: 2018/10/23 01:46:00 by mbiliaie         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME		= 	fractol

SRC			= 	buttons.c \
				dfj.c \
				dfm.c \
				dft.c \
				engine.c \
				validate_start.c

OBJ			= $(addprefix $(OUT_PATH),$(SRC:.c=.o))

CC			=	clang
CFLAGS		= 	-Wall -Wextra -Werror -O3 

LIB_FOLDER 	= 	./libft
LIBFT		= 	./libft/libft.a
LIBINC		= 	-I./libft
LIBLINK		= 	-L./libft -lft

SRCDIR		= 	./src/
INCDIR		= 	./includes/
OUT_PATH	= 	./obj/

all: obj libft $(NAME)

obj:
	mkdir -p $(OUT_PATH)

$(OUT_PATH)%.o:$(SRCDIR)%.c
	@$(CC) $(CFLAGS) $(LIBINC) -I $(INCDIR) -o $@ -c $<

libft: $(LIBFT)

$(LIBFT):
	@make -C $(LIB_FOLDER)

$(NAME): $(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LIBLINK) -lmlx -framework OpenGL -framework AppKit
	@echo "$(NAME) is ready"

clean:
	@make -C $(LIB_FOLDER) fclean
	@rm -rf $(OUT_PATH)
	@rm -rf filler.trace
	@echo "o-files were deleted"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
