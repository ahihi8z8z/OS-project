#!/bin/bash
for i in {1..100}
do 
	echo -e "Lan do thu $i: " >> time_file.txt
	./FileSharing "test/test$i"
	sleep 0.1

done
