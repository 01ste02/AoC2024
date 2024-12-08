#!/bin/bash
NEXTDAY=$(( "$( find . -depth -maxdepth 1 -name 'day*' | sort | tail -n1 | grep -Eo '[0-9]+')" + "1" ))
FOLDER="day${NEXTDAY}"
mkdir -p "${FOLDER}"
ln -s ../templates/Makefile "${FOLDER}/Makefile"
cp -i templates/day/code.c "${FOLDER}/part1.c" 
cd "${FOLDER}"

