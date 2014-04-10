#!/bin/bash

it_limit=50
reruns=20

for i in $(seq 1 $it_limit)
do
	for j in $(seq 1 $reruns)
	do
		output=`../mybins/cs296_4_exe $i`
		file_name="g04out-$i-$j.txt"
		echo "$output" > "../data/$file_name"
	done
done
