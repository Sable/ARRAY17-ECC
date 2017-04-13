#!/bin/bash

SETSIZE=( 32 64 128 256 )
NUMITER=10
LOGFILE=result_kmeans.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "# Input with temp_$k and power_$k" >> ${LOGFILE}
    echo $NUMITER >> ${LOGFILE}
    #./kmeans -i data/kmeans${k}K -n 1 -k 3 > /dev/null 2>&1
    for i in $(seq 1 $NUMITER)
    do
        ./kmeans -i data/kmeans${k}K -n 1 -k 3 | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}
    done
done

# ./kmeans -i data/kmeans32K -n 1 -k 3
# ./kmeans -i data/kmeans64K -n 1 -k 3
# ./kmeans -i data/kmeans128K -n 1 -k 3
# ./kmeans -i data/kmeans256K -n 1 -k 3


