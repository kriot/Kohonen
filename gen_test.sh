#!/bin/bash

echo "7 2 100" | ./points_round  > t1.dat
echo "3 2 100" | ./points_round  > t2.dat
./unite t1.dat t2.dat > t3.dat

