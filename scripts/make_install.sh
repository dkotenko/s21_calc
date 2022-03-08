#!/usr/bin/bash

path=$1

if [[ ${1:0:1} == "/" ]] ;
then
	sudo install $path
	#sudo mkdir -p $path
	#sudo cp -R . $path ;
else
	echo "installation path must be absolute (starts with '/')";
fi