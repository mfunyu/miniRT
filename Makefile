# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfunyu <mfunyu@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/07/19 22:35:48 by mfunyu            #+#    #+#              #
#    Updated: 2020/10/07 14:59:21 by mfunyu           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc
CFLAGS := -Wall -Wextra -Werror -I./include

NAME := miniRT
LIBFT := ./libft/libft.a
LIBMLX := ./minilibx/libmlx.dylib
SRCS := $(wildcard ./get_next_line/*.c)\
		$(wildcard ./src/*.c)
OBJS := $(SRCS:.c=.o)
UNAME := $(shell uname)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
ifeq ($(UNAME), Darwin)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) libmlx.dylib
else
ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -L. -lmlx_Linux -L/usr/include/../lib -lXext -lX11 -lm
endif
endif

$(LIBFT): FORCE
	make -C ./libft

FORCE:

clean:
	$(RM) $(OBJS)
	make clean -C ./libft

fclean: clean
	$(RM) $(NAME) leakscheck
	make fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re FORCE


###============ Additional Use ===============###

leaks : $(OBJS) $(LIBFT)
ifeq ($(UNAME), Darwin)
	$(CC) $(CFLAGS) -g -o leakscheck $(OBJS) $(LIBFT) libmlx.dylib
	# leaks -atExit -- ./leakscheck "
else
ifeq ($(UNAME), Linux)
	$(CC) $(CFLAGS) -g -fsanitize=address -o leakscheck $(NAME) $(OBJS) $(LIBFT) -L. -lmlx_Linux -L/usr/include/../lib -lXext -lX11 -lm
	# ./leakscheck "
endif
endif

clear :
	rm -rf *.bmp
	rm -Rf *.dSYM
	rm leakscheck
