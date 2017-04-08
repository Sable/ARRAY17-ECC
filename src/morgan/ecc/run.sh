#!/bin/bash
# 256 / 512 / 1024 / 2048
if [ "$#" -ne 1 ]; then
    n=0
else
    n=$1
fi

arg_list=( 128 256 512 1024 )
id=${arg_list[${n}]}

arg=data/in_${id}K
log=morgan${n}.log

rm -f ${log}
echo "#Input with ${arg}" > ${log}
echo "5" >> ${log}

echo "Executing $arg 5 times"

## warm up
./mg ${arg} &> /dev/null
for i in {1..5}
do
    ./mg ${arg} | grep "elapsed time" | awk -F\: '{print $2}' >> ${log}
done

echo ".. Saved to ${log}"

