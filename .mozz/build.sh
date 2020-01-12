#! /bin/sh
make -C /Users/tvanessa/Printf re 1>/dev/null 
make -C /Users/tvanessa/Printf clean 1>/dev/null
gcc -g -Wall -Wextra -Werror main.c -I . -I libft -L libft