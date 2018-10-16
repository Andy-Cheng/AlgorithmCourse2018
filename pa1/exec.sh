#!/bin/bash

bash ./clean.sh
rm result.txt
echo touch result.txt
touch result.txt

echo start merge
for filenum in $(seq 1 4)
do  
    echo "merge case ${filenum}" >> result.txt
    ./mergeSort ./case${filenum}.dat m${filenum} >> result.txt
done

echo start heap
for filenum in $(seq 1 4)
do
    echo "heap case ${filenum}" >> result.txt
    ./heapSort ./case${filenum}.dat h${filenum} >> result.txt
done

echo start quick
for filenum in $(seq 1 4)
do
    echo "quick case ${filenum}" >> result.txt
    ./quickSort ./case${filenum}.dat q${filenum} >> result.txt
done 