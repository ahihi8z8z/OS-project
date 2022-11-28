#!/bin/bash
cd "/home/aothatday1/hdh/message_queue/" && rm result1.txt
gcc MessageQueue.c -o MessageQueue 
echo -e "Moi lan do, ket qua co dang sau: (i+(w,r)+result) \n- Trong do i = 1 la thoi gian bat dau, = 2 la thoi gian ket thuc, = 3 la RAM su dung. \n- w: tien trinh ghi, r: tien trinh doc.\n- Ket qua thoi gian co dang %ld second + %ld nanosecond, ket qua RAM tinh bang kb.\n" >> result1.txt
for i in {1..50}
do 
	echo -e "Lan do thu $i: " >> result1.txt
	./MessageQueue
	sleep 0.1

done