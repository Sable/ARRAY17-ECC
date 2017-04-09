#!/bin/bash

SETSIZE=( 100000 200000 400000 800000 )
NUMITER=10
LOGFILE=result_rprime.log

rm -f $LOGFILE
make

for k in "${SETSIZE[@]}"
do
    echo "# Input with n = $k" >> ${LOGFILE}
    echo $NUMITER >> ${LOGFILE}
    #./rprime $k > /dev/null 2>&1
    for i in $(seq 1 $NUMITER)
    do
        ./rprime $k | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}
    done
done

# ./rprime 100000
# ./rprime 200000
# ./rprime 400000
# ./rprime 800000
