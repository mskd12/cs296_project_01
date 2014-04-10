#!/bin/bash
csvfile="../data/g04_lab05data_01.csv"
all_files=`ls ../data`
rm -rf $csvfile
iterations=50
reruns=20

for i in $(seq 1 $iterations)
do
	for j in $(seq 1 $reruns)
	do
		echo -ne "$i," >> $csvfile
		echo -ne "$j" >> $csvfile
		file="g04out-"$i"-"$j".txt"
		cat "../data/$file" | awk '
	        {
			if (NR == 1 || NR == 6) {
	                } else {
				time=NF-1
			        printf "," $time >> "'$csvfile'"
			}
		}
        	'
		echo >> $csvfile
	done
done


