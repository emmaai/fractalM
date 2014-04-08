#!/bin/bash

#PBS -P fh0
#PBS -N FracHomeo
#PBS -l wd

#PBS -l ncpus=1
#PBS -l mem=24gb
#PBS -l walltime=0:09:59

#PBS -o Test_mem.out
#PBS -e Test_mem.err
#PBS -M brendan.harding@anu.edu.au
#PBS -m abe

module list

export OMP_NUM_THREADS=1

./a.out
