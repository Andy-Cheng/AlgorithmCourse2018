#! bin/bash
echo start clean up
prefix=( "i" "m" "h" "q" )

for pre in "${prefix[@]}"
do
    for num in $(seq 1 4)
    do  
        rm ${pre}${num}
    done
done