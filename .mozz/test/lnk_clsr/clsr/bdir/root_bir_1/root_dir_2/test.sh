# !/bin/zsh
cmd="ls "
green='\33[0;32m'
red='\33[0;31m'
reset='\33[0m'
ok="+++ DONE +++"
fail="--- FAIL ---${reset}"
tn=0

echo "=== TEST $tn ==="
f="-1" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1A" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1a" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aA" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aAl" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aAlR" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aAR" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aR" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1R" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1R .." 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1R clsr" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aR clsr" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aRl clsr" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aRl lnk_mouli" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aRl lnk_mouli ." 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

echo "=== TEST $tn ==="
f="-1aRl lnk_mouli . clsr" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))
exit

echo "=== TEST $tn ==="
f="-1aR lnk_mouli . clsr" 
echo $cmd $f
ft_ls $f &>../ft_clsr && ls $f &>../ls_clsr
diff --brief ../ls_clsr ../ft_clsr
if [ $? == 0 ]
then
echo $ok
else 
diff ../ls_clsr ../ft_clsr
echo $fail
fi
tn=$((tn + 1))

