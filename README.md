Reverse Time Migration with provenance data capture

## Overview

This repository presents RTM-UQ integrated with DfAnalyzer, a dataflow tool for monitoring, debugging, steering, and analyzing dataflow paths of scientific applications.

## Software requirements

The following softwares have to be configured / installed for running this application.

1. [DfAnalyzer](https://hpcdb.github.io/armful/dfanalyzer.html) as the tool for capturing and analyzing data of scientific workflows . (Please read the [tutorial](https://gitlab.com/ssvitor/dataflow_analyzer) to download, configure and start)
2. [dfa-lib-cpp](https://gitlab.com/ssvitor/dataflow_analyzer#c-library-dfa-lib-cpp), the C/C++ library to support requests of DfAnalyzer
3. [Intel MPI](https://software.intel.com/en-us/mpi-library), please follow their [get started steps](https://software.intel.com/en-us/mpi-library/documentation/get-started)


In order to run this application, you must execute the following steps:

```bash
cd MC-RTM_ISO_INSTRUMENTADA
make dataflow
make 

./dataflow
mpirun -n 1 ./mpi-rtm_iso2d

```
# Contact
 lneves@cos.ufrj.br
