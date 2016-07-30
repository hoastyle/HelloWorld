#!/bin/bash

# backquote be used to execute the command and return the result
# $1 first parameter
module_name=$1
a=`lsmod | grep char`
trash=/dev/null

# if hello_world had already been loaded, then remove it
echo "$a"
# three ways to judge $a is null or not
# if [ "$a" != "" ]
# if [ -n "$a" ]
if [ x"$a" != x ]
then
	sudo rmmod $module_name 
	echo "$module_name already exist in system, first remove it."
fi

make > $trash
gcc char_app.c -o char_app > $trash
sudo insmod $module_name.ko > $trash
# get major and minor from dmesg
major=`dmesg | tail -1 | awk '{print $4}' | cut -c 1-3`
minor=`dmesg | tail -1 | awk '{print $7}'`
# create dev node for device
sudo mknod /dev/chr_dev c $major $minor
echo "Load $module_name."
echo "Driver debug message:" > info
dmesg | tail -5 >> info
# how to output a empty line to file
echo >> info
echo "lsmod info:" >> info
lsmod >> info
./char_app
echo >> info
echo "char_app info:" >> info
dmesg | tail -2 >> info
sudo rmmod $module_name > $trash
sudo rm /dev/chr_dev
echo "Remove $module_name."
# how to remote file node
# rm /dev/chr_dev
make clean > $trash
echo "Clean the workspace."
