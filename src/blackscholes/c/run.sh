#!/bin/bash

SETSIZE=(1 2 4 8 )
NUMITER=5
LOGFILE=run1.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "echo # Input with in_${k}M.txt >> ${LOGFILE}"
    echo "echo $NUMITER >> ${LOGFILE}"
    for i in $(seq 1 $NUMITER)
    do
        echo "./blackscholes 1 in_${k}M.txt data/in_${k}M.txt data/out_${k}M.txt grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}"
    done
done

#./blackscholes 1 in_1M.txt out_1M.txt
#./blackscholes 1 in_2M.txt out_2M.txt
#./blackscholes 1 in_4M.txt out_4M.txt
#./blackscholes 1 in_8M.txt out_8M.txt
