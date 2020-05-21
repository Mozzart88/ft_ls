#! /bin/sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes --leak-resolution=high --read-inline-info=yes --read-var-info=yes --show-error-list=yes $1