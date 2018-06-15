#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
FILES=($(ls -d $@/*))
for f in "${FILES[@]}"
do
	output=$(./diff.sh $f 2>&1)
	f="$(basename $f)"
	if [ "$output" = "" ]
	then
		echo -e "${GREEN}$f OK"
	else
		echo -e "${RED}$f FAILED"
	fi
done
