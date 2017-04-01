#!/bin/bash
if [ "$#" -ne 1 ]; then
    id=1
else
    id=$1
fi

arg=data/d${id}M/BlkSchls
log=blackscholes${id}.log

rm -f ${log}

echo "Executing $arg 5 times"

## warm up
./bs ${arg} &> /dev/null
for i in {1..5}
do
    ./bs ${arg} >> ${log}
done

echo ".. Saved to ${log}"

