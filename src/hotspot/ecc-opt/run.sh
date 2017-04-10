#!/bin/bash
# 256 / 512 / 1024 / 2048
if [ "$#" -ne 1 ]; then
    n=0
else
    n=$1
fi

arg_list=( 256 512 1024 2048 )
id=${arg_list[$n]}

arg=data/hot${id}
log=hotspot${n}.log

rm -f ${log}
echo "#Input with $arg" > ${log}
echo "10" >> ${log}

echo "Executing $arg 10 times"

## warm up
## ./hs ${arg} &> /dev/null
for i in {1..10}
do
    ./hs ${arg} | grep "elapsed time" | awk -F\: '{print $2}' >> ${log}
done

echo ".. Saved to ${log}"

