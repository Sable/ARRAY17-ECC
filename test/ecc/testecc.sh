#!/bin/bash

benchDirs=( blackscholes hotspot kmeans morgan rprime )
#benchDirs=( morgan )

echo === List of benchmarks ===

count=0
for each in "${benchDirs[@]}"
do
    echo ${count}. $each
    ((count++))
done

echo

echo === Building experiments ===

count=0
for each in "${benchDirs[@]}"
do
    echo ${count}. "../../src/$each/ecc/" | tr -d '\n'
    make -C "../../src/$each/ecc/" > /dev/null 2>&1
    STATUS=${PIPESTATUS[0]}
    if [ $STATUS -eq 0 ]
    then
        echo -n -e " \033[0;32m[pass]\033[0m"
    else
        echo -n -e " \033[0;31m[fail]\033[0m"
    fi
    echo 
    ((count++))
done

echo === Running experiments ===

count=0
for each in "${benchDirs[@]}"
do
    for k in {0..3}
    do
        echo ${count}. "../../src/$each/ecc/ $k"
        (cd ../../src/$each/ecc && ./run.sh $k)
        STATUS=${PIPESTATUS[0]}
        if [ $STATUS -eq 0 ]
        then
            echo -e "\033[0;32m[pass]\033[0m"
        else
            echo -e "\033[0;31m[fail]\033[0m"
        fi
    done
    LOGFILE=result_${each}.log
    #echo " Copying $LOGFILE to current directory"
    cat ../../src/$each/ecc/${each}*.log > ${LOGFILE}
    echo "Result [$each]:"
    ../calculate $LOGFILE
    ((count++))
done


