#! /bin/sh
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=yes -s $1