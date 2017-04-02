#!/bin/bash
# 32 / 64 / 128 / 256
if [ "$#" -ne 1 ]; then
    n=0
else
    n=$1
fi

arg_list=( 32 64 128 256 )
id=${arg_list[$n]}

arg=data/kmeans${id}K
log=kmeans${n}.log

rm -f ${log}
echo "#Input with ${arg}" > ${log}
echo "5" >> ${log}

echo "Executing $arg 5 times"

## warm up
./km ${arg} &> /dev/null
for i in {1..5}
do
    ./km ${arg} | grep "elapsed time" | awk -F\: '{print $2}' >> ${log}
done

echo ".. Saved to ${log}"

