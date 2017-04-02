#!/bin/bash

SETSIZE=( 128 256 512 1024 )
NUMITER=5
LOGFILE=result_morgan.log

rm -f $LOGFILE

make

for k in "${SETSIZE[@]}"
do
    echo "# Input with in_${k}K" >> ${LOGFILE}
    echo $NUMITER >> ${LOGFILE}
    ./morgan < data/in_${k}K.txt > /dev/null 2>&1
    for i in $(seq 1 $NUMITER)
    do
        ./morgan < data/in_${k}K.txt | grep "elapsed time" | awk -F\: '{print $2}' >> ${LOGFILE}
    done
done

# ./morgam < morgan1
# ./morgam < morgan2
# ./morgam < morgan4
# ./morgam < morgan8
