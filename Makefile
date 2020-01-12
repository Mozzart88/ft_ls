# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvanessa <tvanessa@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 15:27:16 by tvanessa          #+#    #+#              #
#    Updated: 2020/01/12 14:57:29 by tvanessa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = ./
SS = $(S)main.c
H = -I . -I libft
NAME = ft_ls
CC = gcc
GCF = -g3 -Wall -Wextra -Werror
CF = -Wall -Wextra -Werror
CL = -L libft/ -lft
CI = -I . -I libft/

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(GCF) $(H) -c -o $@ $<

$(NAME): $(SS:.c=.o)
	@$(CC) $(CF) $(H) -o $(NAME) $(SS:.c=.o) $(CI) $(CL)
	@# ar rc $(NAME) $(SS:.c=.o)

clean:
	make -C libft/ clean
	/bin/rm -f $(SS:.c=.o)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
