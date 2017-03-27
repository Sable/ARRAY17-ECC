#!/bin/bash

SETSIZE=( 1 2 4 8 )
NUMITER=5
LOGFILE=result_morgan.log

rm -f $LOGFILE

for k in "${SETSIZE[@]}"
do
    echo "echo # Input with morgan${k} >> ${LOGFILE}"
    echo "echo $NUMITER >> ${LOGFILE}"
    for i in $(seq 1 $NUMITER)
    do
        echo "./morgan < morgan${k} | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}"
    done
done

# ./morgam < morgan1
# ./morgam < morgan2
# ./morgam < morgan4
# ./morgam < morgan8
