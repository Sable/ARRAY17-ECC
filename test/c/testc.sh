#!/bin/bash

#benchDirs=( blackscholes hotspot kmeans morgan rprime )
benchDirs=( kmeans )

start_time=`date +%s`

echo === List of benchmarks ===

count=0
for each in "${benchDirs[@]}"
do
    echo "${count}) $each"
    ((count++))
done

echo

echo === Building experiments ===

count=0
for each in "${benchDirs[@]}"
do
    echo ${count}. "../../src/$each/c/" | tr -d '\n'
    make -C "../../src/$each/c/" &> /dev/null
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
    echo ${count}. "../../src/$each/c/"
    (cd ../../src/$each/c && ./run.sh)
    STATUS=${PIPESTATUS[0]}
    if [ $STATUS -eq 0 ]
    then
        echo -e "\033[0;32m[pass]\033[0m"
    else
        echo -e "\033[0;31m[fail]\033[0m"
    fi
    LOGFILE=result_${each}.log
    #echo " Copying $LOGFILE to current directory"
    cp ../../src/$each/c/$LOGFILE $LOGFILE
    echo "Result [$each]:"
    ../calculate $LOGFILE
    ((count++))
done

end_time=`date +%s`

echo execution time was `expr $end_time - $start_time` s.
