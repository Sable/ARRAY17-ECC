#!/bin/bash
# 256 / 512 / 1024 / 2048
if [ "$#" -ne 1 ]; then
    id=256
else
    id=$1
fi

arg=data/in_${id}K
log=morgan${id}.log

rm -f ${log}

echo "Executing $arg 5 times"

## warm up
./mg ${arg} &> /dev/null
for i in {1..5}
do
    ./mg ${arg} >> ${log}
done

echo ".. Saved to ${log}"

