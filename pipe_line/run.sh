#!/bin/bash
echo -e "Ket qua do se co dang sau : \n Time process 1 start write to pipe: %ld second + %ld nanosecond \n Time process 1 stop write to pipe: %ld second + %ld nanosecond \n Time process 2 start read from pipe: %ld second + %ld nanosecond \n Time process 2 stop read from pipe: %ld second + %ld nanosecond \n" >> time_pipe.txt
for i in {1..50}
do 
	echo -e "Lan do thu $i: " >> time_pipe.txt
	./PipeLine 
	sleep 0.1

done
