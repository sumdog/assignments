#!/bin/bash

if [ "$1" == "" ]; then
  echo "Please specify either \"soy\" or \"cars\" for argument 1";
  exit 2;
fi

filelist=([0]=01 [1]=02 [2]=03 [3]=04 [4]=05 [5]=06 [6]=07 [7]=08 [8]=09 [9]=10);

for i in 0 1 2 3 4 5 6 7 8 9 
do
  ./csc4240-program4.exe data/$1_train_${filelist[i]}.txt data/$1_test_${filelist[i]}.txt
done
