#!/bin/bash

SETSIZE=( 256 512 1024 2048 )
NUMITER=5
LOGFILE=result_hotspot.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "echo # Input with temp_$k and power_$k >> ${LOGFILE}"
    echo "echo $NUMITER >> ${LOGFILE}"
    for i in $(seq 1 $NUMITER)
    do
        echo "./hotspot $k $k 20 1 data/temp_$k data/power_$k | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}"
    done
done


# ./hotspot 256 256 20 1 temp_256 power_256
# ./hotspot 512 512 20 1 temp_512 power_512
# ./hotspot 1024 1024 20 1 temp_1024 power_1024
# ./hotspot 2048 2048 20 1 temp_2048 power_2048


