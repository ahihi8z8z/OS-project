#!/bin/bash
echo -e "Ket qua do se co dang sau : \n Time process 1 start send message to queue: %ld second + %ld nanosecond \n Time process 1 stop send message to queue: %ld second + %ld nanosecond \n Time process 2 start read message from queue: %ld second + %ld nanosecond \n Time process 2 stop read message from queue: %ld second + %ld nanosecond \n" >> time_message_queue.txt
for i in {1..50}
do 
	echo -e "Lan do thu $i: " >> time_message_queue.txt
	./MessageQueue
	sleep 0.1

done