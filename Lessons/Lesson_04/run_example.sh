#!/bin/bash
if [ $# = 0 ]; then
   file_name="`ls -lt *.cpp | head -n 1 | gawk '{print $9}'`"
else
   file_name="$1"
fi

echo "--------- Now compiling ---------"
echo "$file_name"
g++ -pthread -std=c++11 "$file_name"

echo "--------- kich a.out ------------"
./a.out
