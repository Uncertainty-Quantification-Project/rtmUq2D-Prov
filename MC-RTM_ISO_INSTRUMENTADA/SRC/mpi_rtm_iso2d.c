#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h>

#include "fixed_parameters.h"
#include "rtm_iso2d.h"
#include "dfanalyzer.h"

void main(void) {

	//----------------------------------------------------------------
	// MPI Variables...
	char processor_name[MPI_MAX_PROCESSOR_NAME];
	int world_size, rank, name_len;
	float simulations_per_node;
	double start, end;
	
	int simulation_index;
	int first_simulation, last_simulation;
// 	int numberOfSimulations;
	//----------------------------------------------------------------
	
	
	MPI_Init(NULL, NULL);
	
	// Get the number of processes...
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	
	// Get the rank of the process...
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	// Get the name of the processor...
	MPI_Get_processor_name(processor_name, &name_len);
	
// 	printf("\n\n.................................... STARTING 2D ISOTROPIC REVERSE TIME MIGRATION !!! ..........\n");
	printf("[Host %s] [MPI rank %d] %s \n", processor_name, rank, "STARTING 2D ISOTROPIC REVERSE TIME MIGRATION !!!");
	
// 	// Total number of simulations...
// 	numberOfSimulations = 2;
	
	// Number of simulations per node...
	simulations_per_node = ( (float)numberOfSimulations ) / world_size;
	
	// Simulation ranges...
	first_simulation = (int) (ceil((simulations_per_node * rank) + 1)) ;
	last_simulation  = (int) (ceil( simulations_per_node * (rank + 1)));
	
// 	printf("[Host %s] [MPI rank %d] %d %d %d\n", processor_name, rank, (int)ceil(simulations_per_node), first_simulation, last_simulation);
	
	start = MPI_Wtime();
	for (simulation_index = first_simulation; simulation_index <= last_simulation; simulation_index++) {

// 		printf("[Host %s] [MPI rank %d] I %d \n", processor_name, rank, simulation_index);
		rtm_routine(simulation_index);
	
	}
	end = MPI_Wtime();
// 	
	printf("--> The process %d took %lf seconds to run.\n", rank, end - start);

	Task task_execution =Task("rtm", "execution",3 );
    vector<string> transformation_tags = {"stacking"};
    task_execution.add_dependent_transformation_tags(transformation_tags);
    task_execution.add_dependent_transformation_id(2);


    vector<string> oexecution_values = {std::to_string(last_simulation), std::to_string(end-start)};
    Dataset& ds_oexecution = task_execution.add_dataset("oexecution");
    ds_oexecution.add_element_with_values(oexecution_values);
    task_execution.begin();

    task_execution.end();    
	
	MPI_Finalize();
}
