#Create a script to rename all files with a ".txt" extension in a directory to have a ".bak" extensions


#!/bin/bash


read -p "Enter directory name: " dir


for file in *.txt #check file type of extension .txt
do 
	mv $file `echo $file | sed 's/\(.*\.\)txt/\1bak/'`
	#mv is use to rename and sed is use to check expression
	# | is use ouput of the echo is set as input of sed option
done
