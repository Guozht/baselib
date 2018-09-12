#!/bin/bash

if [[ (-e ./man) ]] ; then
  rm -r ./man
fi
mkdir man

cp ./_man/* ./man
for man_file in `ls ./man`
do
  gzip -n ./man/$man_file
done
