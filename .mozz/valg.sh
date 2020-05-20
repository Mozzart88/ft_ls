#! /bin/sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes --leak-resolution=med --show-error-list=yes $1