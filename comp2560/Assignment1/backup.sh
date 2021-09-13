#!/bin/bash

# Assignment 1
# Developer: Dennis Dao
# Date: January 20, 2021
# Student Number: 110010116

# This script backs up a list of files

# Check for incorrect usage of script:
# Invalid number of arguments
if [ $# == 0 ] ; then
	echo "Not enough arguments"
	echo "Usage: $0 [-t target-dir] <suffix-list...>"
	exit 1

# Incorrect number of arguments with -t (-t some_directory)
elif ([ $1 == -t ] && [ $# -le 2 ]) ; then
	echo "Too few arguments with -t"
        echo "Usage: $0 [-t target-dir] <suffix-list...>"
	exit 1

# The target is not a directory
elif [ $1 == -t ] && [ ! -d $2 ] ; then
	echo "$2 is not a directory or doesn't exist"
        echo "Usage: $0 [-t target-dir] <suffix-list...>"
	exit 1
fi

# Prep the directory name
dirName=`date | tr -d " :"`
# Default target is current directory
targetDir="."
let "i = 0"

# Change target directory if -t used
if [ $1 == -t ] && [ -d $2 ] ; then
	targetDir=$2
	let "i = 2"
fi

# Make the new directory in target directory
cd $targetDir
mkdir $dirName

# Get the extensions
argv=( $* )
N=$(( $# - $i ))
extensions=${argv[@]:$i:$N}

# Copy and delete the source files of each extension
for ext in $extensions ; do
	for file in `ls *.$ext` ; do
		cp $file $dirName
		rm $file
	done
	echo -n "$ext files copied "
done

# Make the archive
`tar -cf archive.tar $dirName`
echo -n "tar file created"
echo ""

# Success message
echo "./$dirName/archive.tar source files deleted"
exit 0
