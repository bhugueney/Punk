#!/usr/bin/env bash
cd ./bin
mpirun -quiet -n 32 ./abs_ssp_cluster universe.txt 0