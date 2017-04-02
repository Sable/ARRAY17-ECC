#!/bin/bash
# 256 / 512 / 1024 / 2048
if [ "$#" -ne 1 ]; then
    id=256
else
    id=$1
fi

arg=data/hot${id}
log=hotspot${id}.log

rm -f ${log}

echo "Executing $arg 5 times"

## warm up
./hs ${arg} &> /dev/null
for i in {1..5}
do
    ./hs ${arg} >> ${log}
done

echo ".. Saved to ${log}"

