# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 15:27:16 by tvanessa          #+#    #+#              #
#    Updated: 2020/05/19 14:30:29 by mozzart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = ./
SS = $(S)main.c ft_new_rec.c ft_sort.c merge_sort.c vector.c ft_fs_functions.c ft_pargs.c ft_errors.c ft_fs_filetype.c ft_time.c ft_pwd.c ft_gr.c ft_print_rifo.c ft_readdir.c ft_print_all.c ft_new_mvl.c ft_print_files.c ft_print_dirs.c ft_ls.c ft_destroy_rec.c ft_sort_by_time.c
H = -I . -I libft -I libft/ft_printf
NAME = ft_ls
CC = clang
CF = -Wall -Wextra -Werror -g
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
