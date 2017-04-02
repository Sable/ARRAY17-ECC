#!/bin/bash
if [ "$#" -ne 1 ]; then
    n=0
else
    n=$1
fi

arg_id=( 1 2 4 8 )
id=${arg_id[$n]}

arg=data/d${id}M/BlkSchls
log=blackscholes${n}.log

rm -f ${log}
echo "#Input with $arg" > ${log}
echo "5" >> ${log}

echo "Executing $arg 5 times"

## warm up
./bs ${arg} &> /dev/null
for i in {1..5}
do
    ./bs ${arg} | grep "elapsed time" | awk -F\: '{print $2}' >> ${log}
done

echo ".. Saved to ${log}"

