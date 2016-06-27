#!/bin/bash

# backquote be used to execute the command and return the result
a=`lsmod | grep hello_world`
trash=/dev/null

# if hello_world had already been loaded, then remove it
echo "$a"
# three ways to judge $a is null or not
# if [ "$a" != "" ]
# if [ -n "$a" ]
if [ x"$a" != x ]
then
	sudo rmmod hello_world
	echo "hello_world already exist in system, first remove it."
fi

make > $trash
sudo insmod hello_world.ko > $trash	
echo "Load hello_world."
echo "Driver debug message:" > info
dmesg | tail -5 >> info
echo >> info
echo "lsmod info:" >> info
lsmod >> info
sudo rmmod hello_world > $trash
echo "Remove hello_world."
make clean > $trash
echo "Clean the workspace."
