#!/bin/bash

SETSIZE=( 10000 20000 40000 80000 )
NUMITER=5
LOGFILE=result_rprime.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "echo # Input with n = $k >> ${LOGFILE}"
    echo "echo $NUMITER >> ${LOGFILE}"
    for i in $(seq 1 $NUMITER)
    do
        echo "./rprime $k | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}"
    done
done

# ./rprime 10000
# ./rprime 20000
# ./rprime 40000
# ./rprime 80000
