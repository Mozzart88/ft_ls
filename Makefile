# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mozzart <mozzart@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/04 15:27:16 by tvanessa          #+#    #+#              #
#    Updated: 2020/05/31 14:03:55 by mozzart          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

S = ./
SS = $(S)main.c ft_new_rec.c ft_sort.c merge_sort.c vector.c ft_fs_functions.c ft_pargs.c ft_errors.c ft_fs_filetype.c ft_time.c ft_pwd.c ft_gr.c ft_print_rifo.c ft_readdir.c ft_print_all.c ft_new_mvl.c ft_print_files.c ft_print_dirs.c ft_ls.c ft_destroy_rec.c ft_sort_by_time.c ft_reset_rec.c ft_time_format_print.c
LIBSS = ft_new_rec.c ft_sort.c merge_sort.c vector.c ft_fs_functions.c ft_pargs.c ft_errors.c ft_fs_filetype.c ft_time.c ft_pwd.c ft_gr.c ft_print_rifo.c ft_readdir.c ft_print_all.c ft_new_mvl.c ft_print_files.c ft_print_dirs.c ft_ls.c ft_destroy_rec.c ft_sort_by_time.c ft_reset_rec.c ft_time_format_print.c
H = -I . -I .. -I ../ft_printf  -I libft -I libft/ft_printf
NAME = ft_ls
LIBNAME = libftls.a
VNAME = vls
CC = clang
CF = -Wall -Wextra -Werror -g
CL = -L libft/ -lft
CI = -I . -I libft/ -I ..

all: $(NAME)

%.o: %.c $(NAME).h
	$(CC) $(CF) $(H) -c -o $@ $<

$(NAME): $(SS:.c=.o)
	@make -C libft
	@$(CC) $(CF) $(H) -o $(NAME) $(SS:.c=.o) $(CL)

clean:
	make -C libft/ clean
	/bin/rm -f $(SS:.c=.o)

fclean: clean
	make -C libft/ fclean
	/bin/rm -f $(NAME)

re: fclean all

lib: $(LIBSS:.c=.o)
	ar r $(LIBNAME) $(LIBSS:.c=.o)
	ranlib $(LIBNAME)

libclean: 
	/bin/rm -f $(LIBSS:.c=.o)

libfclean:  libclean
	/bin/rm -f $(LIBNAME)
