#!/bin/bash
# 1 / 2 / 4 / 8
if [ "$#" -ne 1 ]; then
    id=1
else
    id=$1
fi

arg=data/"in${id}00K"
log=rprime${id}.log

rm -f ${log}

echo "Executing $arg 5 times"

## warm up
./rp ${arg} &> /dev/null
for i in {1..5}
do
    ./rp ${arg} >> ${log}
done

echo ".. Saved to ${log}"

