#!/bin/bash
echo -e "Ket qua do se co dang sau : \n Time process 1 start write to file: %ld second + %ld nanosecond \n Time process 1 stop write to file: %ld second + %ld nanosecond \n Time process 2 start read from file: %ld second + %ld nanosecond \n Time process 2 stop read from file: %ld second + %ld nanosecond \n" >> time_file.txt
for i in {1..50}
do 
	echo -e "Lan do thu $i: " >> time_file.txt
	./FileSharing "test/test$i"
	sleep 0.1

done
