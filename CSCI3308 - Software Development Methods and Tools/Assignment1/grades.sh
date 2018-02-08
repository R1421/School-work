#!/bin/bash
## Raymond Duncan

#if [ sudo -w ` /dev/stdin ` != $1 ]
#then
#	echo "Usage grades.sh filename"
#fi
#a1=${1:-/dev/stdin}
#a2=${2:-/dev/stdin}
if [ ${1:-/dev/stdin} == "/dev/stdin" ] || [ ${2:-/dev/stdin} != "/dev/stdin" ]
then
	echo "Usage: grades.sh filename"
	exit
fi

a1=${1:-/dev/stdin}
echo $a1

while read line
do
	arr=($line)
	avg=$(((arr[3] + arr[4] + arr[5]) / 3))
	last=${arr[2]}
	first=${arr[1]}
	ID=${arr[0]}
	echo "$avg [$ID] $last, $first"
done < $a1 | sort -k 3 -k 2
