#!/bin/bash
# run two writers at the same time and count lines

rm -f output.txt

./writer.sh A &
./writer.sh B &
wait

echo "Total lines in output.txt:"
wc -l output.txt

echo "Lines from A:"
grep -c "^A" output.txt

echo "Lines from B:"
grep -c "^B" output.txt
