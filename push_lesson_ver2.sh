#!/bin/bash
if [ $# = 0 ]; then
   comments="update lesson files"
else
   comments="$1"
fi

git add .
git commit -m "$comments"
git push -u origin master

echo $comments
