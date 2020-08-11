#!/bin/bash
if [ $# = 0 ]; then
    echo "Please type file name"
    exit 0
else
   file_name="$1"
fi

echo "--------- Now compiling ---------"
g++ -pthread -std=c++11 "$file_name"

echo "--------- kich a.out ------------"
./a.out
