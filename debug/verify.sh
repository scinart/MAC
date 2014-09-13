#!/bin/bash

limit=100;
cd $1
stdtime="0.00"
mytime="0.00"
make -f ../Makefile all
for ((n=0;n<$limit;n++)); do
    ./gen >| data
    stdtime=$(echo $stdtime + $({ /usr/bin/time -f "%U" ./std < data >| std.out;} 2>&1) | bc )
    mytime=$(echo $mytime + $({ /usr/bin/time -f "%U" ./my  < data >| my.out;} 2>&1) | bc )
    /usr/bin/diff -Bwq std.out my.out
    if [ $? -eq 1 ]; then
	break;
    fi
done
echo std:$stdtime
echo my:$mytime
