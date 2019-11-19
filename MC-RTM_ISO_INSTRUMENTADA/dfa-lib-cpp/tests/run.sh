#!/bin/bash

#set -x
export DFANALYZER_DIR=../../../applications/dfanalyzer/dfa
export LIBMESH_DIR=/program/libmesh
export FASTBIT=/program/fastbit-2.0.3
export PARAVIEW=/program/paraview-v5.5.0
source run_common.sh

example_name=dataflow_test

export DFA_LIB=../../dfa-lib-cpp
export LD_LIBRARY_PATH=$DFA_LIB/lib:$LD_LIBRARY_PATH

echo $LD_LIBRARY_PATH

run_example "$example_name" 
