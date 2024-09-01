#!/bin/bash

cd `dirname $0`

OPTIONS=`cat $(acc config-dir)/cpp/compile_flags.txt | tr '\n' ' '`

for i in `find . -name "*.hpp"`; do
  target=${i}.gch
  # if [ ! -e $target ] || [ -n "`find $i -newer $target -print`" ]; then
    echo "precompiling $i ..."
    g++ $OPTIONS -x c++-header -o $target $i
  # else
  #   echo "precompile skipped $i"
  # fi
done

