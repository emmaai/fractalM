#!/bin/bash

#PBS -P fh0
#PBS -N FracHomeo
#PBS -l wd

#PBS -l ncpus=16
#PBS -l mem=24gb
#PBS -l walltime=0:59:59

#PBS -o Fractal_Homeo.out
#PBS -e Fractal_Homeo.err
#PBS -M brendan.harding@anu.edu.au
#PBS -m abe

module list

export OMP_NUM_THREADS=8

#make all

./a.out

export OMP_NUM_THREADS=16

./a.out
