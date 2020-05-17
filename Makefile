# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 15:27:16 by tvanessa          #+#    #+#              #
#    Updated: 2020/05/17 12:36:25 by mozzart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = ./
SS = $(S)main.c ft_new_rec.c ft_sort.c merge_sort.c vector.c ft_fs_functions.c ft_pargs.c ft_errors.c ft_fs_filetype.c ft_time.c ft_pwd.c ft_gr.c ft_print_rifo.c ft_readdir.c ft_print_all.c ft_new_mvl.c ft_print_files.c ft_print_dirs.c
H = -I . -I libft -I libft/ft_printf
NAME = ft_ls
ifndef CC
CC=gcc
endif
# DEBUG = $(debug)
ifdef DEBUG
CF = -g3 -Wall -Wextra -Werror
else
CF = -Wall -Wextra -Werror
endif
CL = -L libft/ -lft
CI = -I . -I libft/

all: $(NAME)

%.o: %.c $(NAME).h
	$(CC) $(CF) $(H) -c -o $@ $<

$(NAME): $(SS:.c=.o)
	@make -C libft
	@$(CC) $(CF) $(H) -o $(NAME) $(SS:.c=.o) $(CL)
	@# ar rc $(NAME) $(SS:.c=.o)

clean:
	make -C libft/ clean
	/bin/rm -f $(SS:.c=.o)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all
