#!/bin/bash
## Raymond Duncan

if [ $# != 1 ] 
then 
	echo "Usage: grades-awk.sh filename"
fi

filename=$1
awk '{ FS=" "; OFMT="%2d"; print (($4+$5+$6)/3),"["$1"]",$3",",$2;}' $filename | sort -k 3 -k 2
