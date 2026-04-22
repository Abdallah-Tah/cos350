#!/bin/bash
# writes 1000 lines to output.txt using >>
# $1 is a label (A or B) so we can tell the lines apart

for i in $(seq 1 1000)
do
    echo "$1 line $i" >> output.txt
done
