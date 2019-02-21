#!/bin/sh
echo "Doing file: $1"
once="$(./main < "$1")"
twice="$(./main < "$1" | ./main)"

if [ "$once" != "$twice" ]; then
    echo "$once" > /tmp/once_diff1
    echo "$twice" > /tmp/twice_diff2
    echo "DIFFERS: diff of once | twice "
    diff -y /tmp/once_diff1 /tmp/twice_diff2
else
    echo "SAME!"
fi

