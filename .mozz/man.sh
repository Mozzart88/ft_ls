#! /bin/sh
MP=$1 
URL="/Users/mozzart/Documents/GitHub/ft_ls/.mozz/man/man_$(echo $MP | tr ' ' '_').html"
LINE="  \<script src=\"..\/download.js\"\>\<\/script\>"
mandoc -O style=../man.css -Thtml $(man -w $MP) | awk -v l="$LINE" 'NR==6{print l}1' > $URL
