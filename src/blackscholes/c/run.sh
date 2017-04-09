#!/bin/bash

SETSIZE=( 1 2 4 8 )
NUMITER=10
LOGFILE=result_blackscholes.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "# Input with in_${k}M.txt" >> ${LOGFILE}
    echo $NUMITER >> ${LOGFILE}
    #./blackscholes 1 data/in_${k}M.txt data/out_${k}M.txt > /dev/null 2>&1
    for i in $(seq 1 $NUMITER)
    do
        ./blackscholes 1 data/in_${k}M.txt data/out_${k}M.txt | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}
    done
done

#./blackscholes 1 in_1M.txt out_1M.txt
#./blackscholes 1 in_2M.txt out_2M.txt
#./blackscholes 1 in_4M.txt out_4M.txt
#./blackscholes 1 in_8M.txt out_8M.txt
