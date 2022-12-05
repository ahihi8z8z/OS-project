#!/bin/bash
result=result1.txt
soucre_name=MessageQueue.c
exec_name=MessageQueue

rm $result $exec_name msgq.txt
gcc $soucre_name -o $exec_name 
echo -e "Bai test thu 1: gui mot tin nhan dai 2048 byte \n" >>$result
echo -e "Moi lan do, ket qua co dang sau: (i+(w,r)+result) \n- Trong do i = 1 la thoi gian bat dau, = 2 la thoi gian ket thuc, = 3 la RAM su dung. \n- w: tien trinh ghi, r: tien trinh doc.\n- Ket qua thoi gian co dang %ld second + %ld nanosecond, ket qua RAM tinh bang kb.\n" >> $result
for i in {1..50}
do 
	echo -e "Lan do thu $i: " >> $result
	./$exec_name 
	sleep 0.1

done