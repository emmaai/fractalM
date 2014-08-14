#!/bin/bash

#PBS -P fh0
#PBS -N FracHomeo
#PBS -l wd

#PBS -l ncpus=16
#PBS -l mem=24gb
#PBS -l walltime=0:19:59

# Need to set a wall time appropriate for the sequence length
# for the non-safe transformation modes we should have
#   length 12 sequence takes <11 minutes (set 20 minute limit)
#   length 13 sequence takes <90 minutes (set 2 hour limit)
# for the safe transformations we generally have
# about the same time (or even less) as the if() checks are offset
# by less writes to memory
# BE CAREFUL, the embeddings which tile the cube with tetrahedra
# will take longer, up to 5 or 6 times longer depending on the embedding.


#PBS -o Fractal_Homeo.out
#PBS -e Fractal_Homeo.err
#PBS -M brendan.harding@anu.edu.au
#PBS -m abe

module list

export OMP_NUM_THREADS=16

./a.out
