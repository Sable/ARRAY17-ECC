#!/bin/bash
# 32 / 64 / 128 / 256
if [ "$#" -ne 1 ]; then
    id=32
else
    id=$1
fi

arg=data/kmeans${id}K
log=kmeans${id}K.log

rm -f ${log}

echo "Executing $arg 5 times"

## warm up
./km ${arg} &> /dev/null
for i in {1..5}
do
    ./km ${arg} >> ${log}
done

echo ".. Saved to ${log}"

