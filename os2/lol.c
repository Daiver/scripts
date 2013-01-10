#!/bin/bash
for i in `seq 1 100`;
do
	./client uname &
done
