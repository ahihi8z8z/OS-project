#!/bin/bash
echo -e "Ket qua do se co dang sau : \n Time process 1 start write to shared memory: %ld second + %ld nanosecond \n Time process 1 stop write to shared memory: %ld second + %ld nanosecond \n Time process 2 start read from shared memory: %ld second + %ld nanosecond \n Time process 2 stop read from shared memory: %ld second + %ld nanosecond \n" >> time_shared_memory.txt
for i in {1..50}
do 
	echo -e "Lan do thu $i: " >> time_shared_memory.txt
	./SharedMemory
	sleep 0.1

done
