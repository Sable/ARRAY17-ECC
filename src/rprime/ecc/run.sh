#!/bin/bash
# 1 / 2 / 4 / 8
if [ "$#" -ne 1 ]; then
    n=0
else
    n=$1
fi

arg_list=( 1 2 4 8 )
id=${arg_list[${n}]}

arg=data/"in${id}00K"
log=rprime${n}.log

rm -f ${log}
echo "#Input with ${arg}" > ${log}
echo "5" >> ${log}

echo "Executing $arg 5 times"

## warm up
./rp ${arg} &> /dev/null
for i in {1..5}
do
    ./rp ${arg} | grep "elapsed time" | awk -F\: '{print $2}' >> ${log}
done

echo ".. Saved to ${log}"

