#!/bin/bash

SETSIZE=( 256 512 1024 2048 )
NUMITER=10
LOGFILE=result_hotspot.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "# Input with temp_$k and power_$k" >> ${LOGFILE}
    echo $NUMITER >> ${LOGFILE}
    #./hotspot $k $k 20 1 data/temp_$k data/power_$k > /dev/null 2>&1
    for i in $(seq 1 $NUMITER)
    do
        ./hotspot $k $k 20 1 data/temp_$k data/power_$k | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}
    done
done


# ./hotspot 256 256 20 1 data/temp_256 data/power_256
# ./hotspot 512 512 20 1 data/temp_512 data/power_512
# ./hotspot 1024 1024 20 1 data/temp_1024 data/power_1024
# ./hotspot 2048 2048 20 1 data/temp_2048 data/power_2048


