#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

#include "rtm_iso2d.h"
#include "fixed_parameters.h"
#include "generic_functions.h"
#include "forward_modeling.h"
#include "backward_modeling.h"
#include "pi_file.h"
#include "math_functions.h"
#include "dfanalyzer.h"


void rtm_routine(int simulationId) {
	
	int i, k, shotID, nR;
	
    int extensionModel, depthModel;
    int *shotLocation;
    double start, end;
        
	float *velocityModel, *modifiedVelocityModel;
    float *seismogram, *wavelet;
	float *crossCorrelation, *seflSourceCorrelation;
    float *stackCrossCorrelation, *stackSelfCorrelation, *stackCrossCorrelationLaplacian;
	
	char velocityFile_02[VEC_LEN];
	char crossCorrelationFile_02[VEC_LEN];
    char selfSourceCorrelationFile_02[VEC_LEN];
    char crossCorrelationFileLocal[VEC_LEN];
    char stackedFile_02[VEC_LEN];
	char stackedLaplacianFile_02[VEC_LEN];
    char seismogramFile_02[VEC_LEN];
	
	// ++++  Information model dimensions  ++++
	// Nx -> number of points (x-direction) of the original velocity matrix in disk
	// Nz -> number of points (z-direction) of the original velocity matrix in disk
	// extensionModel -> number of points (x-direction) of the original velocity matrix in disk plus the damping layers (left and right)
	// depthModel     -> number of points (z-direction) of the original velocity matrix in disk plus the damping layers (upper and down)
	
	extensionModel = thicknessLeft + Nx + thicknessRight;
    depthModel = thicknessUp   + Nz + thicknessDown;
	
        
	// ++++  Information shot locations  ++++
	// shotLocation[0] = x_shot (x-direction)
	// shotLocation[1] = z_shot (z-direction)
	
	shotLocation            = (int *)  calloc(2, sizeof(int));
	
	
	// ++++  Allocating memory  ++++
	velocityModel 	        = (float *)calloc(Nx*Nz, sizeof(float));
    modifiedVelocityModel 	= (float *)calloc(extensionModel*depthModel, sizeof(float));
    seismogram              = (float *) calloc(numberOfReceivers*numberOfTimeStep, sizeof(float));
	wavelet 	        = (float *)calloc(sampligWavelet, sizeof(float));
    stackSelfCorrelation    = (float *)calloc(Nx*Nz, sizeof(float));
    stackCrossCorrelation	= (float *)calloc(Nx*Nz, sizeof(float));
    stackCrossCorrelationLaplacian = (float *)calloc(Nx*Nz, sizeof(float));
        
	
	printf("\n\n.................................... STARTING 2D ISOTROPIC REVERSE TIME MIGRATION !!! ..........\n");
        
//	+++ Reading data from disk +++
	sprintf(velocityFile_02, velocityFile, simulationId);
	reading_file(velocityFile_02, velocityModel, Nx, Nz);
	reading_file(waveletFile, wavelet, 1, sampligWavelet);
	
    // Adjusting velocity matrix plus damping layers
    extend_matrix(modifiedVelocityModel, velocityModel);
    
    shotLocation[1] = depthShot;
    start = MPI_Wtime();
    int task_id = 1;
    Task task_runrtm= Task("rtm", "runrtm", task_id);

    vector<string> irunrtm_values = {velocityFile_02, waveletFile,std::to_string(Nx), std::to_string(Nz), std::to_string(simulationId)};
    Dataset& ds_irunrtm = task_runrtm.add_dataset("irunrtm");
    ds_irunrtm.add_element_with_values(irunrtm_values);
    for (shotID = 1; shotID <= numberOfShots; shotID++) {
      
        printf("SHOT %d\n", shotID);
        // 	    
        // arithmetic progression of the shot locations...
        shotLocation[0] = firstLocationShot + (shotID - 1)*spacingShot;

        isotropicAcousticModeling(simulationId, shotLocation, modifiedVelocityModel, wavelet);

        sprintf(seismogramFile_02, seismogramFile, shotID);
        reading_file(seismogramFile_02 , seismogram, numberOfReceivers, numberOfTimeStep);

        vector<string> iseismogram_values = {seismogramFile_02, std::to_string(simulationId), std::to_string(shotID)};
        Dataset& ds_iseismogram = task_runrtm.add_dataset("iseismogram");
        ds_iseismogram.add_element_with_values(iseismogram_values);

        task_runrtm.begin();

	    crossCorrelation	  = (float *)calloc(Nx*Nz, sizeof(float));
        seflSourceCorrelation = (float *)calloc(Nx*Nz, sizeof(float));
    
        adjointModeling(simulationId, shotLocation, modifiedVelocityModel, wavelet, seismogram, crossCorrelation, seflSourceCorrelation);
	    
	    sprintf(crossCorrelationFile_02, crossCorrelationFile, shotID, simulationId);
	    recording_file(crossCorrelationFile_02, crossCorrelation, Nx, Nz);
	    free(crossCorrelation);
	    crossCorrelation = NULL;
    
        sprintf(selfSourceCorrelationFile_02, selfSourceCorrelationFile, shotID, simulationId);
	    recording_file(selfSourceCorrelationFile_02, seflSourceCorrelation, Nx, Nz);
	    free(seflSourceCorrelation);
	    seflSourceCorrelation = NULL;

        vector<string> orunrtm_values = {crossCorrelationFile_02, selfSourceCorrelationFile_02,std::to_string(shotID),std::to_string(*shotLocation)};
        Dataset& ds_orunrtm = task_runrtm.add_dataset("orunrtm");
        ds_orunrtm.add_element_with_values(orunrtm_values);

        if (shotID== numberOfShots)
            task_runrtm.end();
        else task_runrtm.save();
    }
    printf("\n\n");
    
    // Stacking...
    crossCorrelation	= (float *)calloc(Nx*Nz, sizeof(float));
    seflSourceCorrelation = (float *)calloc(Nx*Nz, sizeof(float));
    for (shotID = 1; shotID <= numberOfShots; shotID++) {
        
        sprintf(crossCorrelationFile_02, crossCorrelationFile, shotID, simulationId);
        reading_file(crossCorrelationFile_02, crossCorrelation, Nx, Nz);
        
        sprintf(selfSourceCorrelationFile_02, selfSourceCorrelationFile, shotID, simulationId);
        reading_file(selfSourceCorrelationFile_02, seflSourceCorrelation, Nx, Nz);

        for (i = 0; i < Nx; i++) {
            for (k = 0; k < Nz; k++) {
    
                stackCrossCorrelation[i*Nz + k] = stackCrossCorrelation[i*Nz + k] + crossCorrelation[i*Nz + k];
                stackSelfCorrelation[i*Nz + k] = stackSelfCorrelation[i*Nz + k] + seflSourceCorrelation[i*Nz + k];
            }
        }
            
        nR = remove(crossCorrelationFile_02);
	    if( nR == 0 ) {
	    } 
	    else {
        	perror("Error Remove");
    	}
    	    
	    nR = remove(selfSourceCorrelationFile_02);
	    if( nR == 0 ) {
	    } 
	    else {
        	perror("Error Remove");
    	    }
    }
    free(crossCorrelation);     free(seflSourceCorrelation);
	crossCorrelation = NULL;    seflSourceCorrelation = NULL;
	
    for (i = 0; i < Nx; i++) {
        for (k = 0; k < Nz; k++) {
    
            stackCrossCorrelation[i*Nz + k] = stackCrossCorrelation[i*Nz + k] / + stackSelfCorrelation[i*Nz + k];
        }
    }
        
    sprintf(stackedFile_02, stackedFile, simulationId);
    recording_file(stackedFile_02, stackCrossCorrelation, Nx, Nz);
    
    laplacian_filter2D (stackCrossCorrelationLaplacian, stackCrossCorrelation);
    
	sprintf(stackedLaplacianFile_02, stackedLaplacianFile, simulationId);
    recording_file(stackedLaplacianFile_02, stackCrossCorrelationLaplacian, Nx, Nz);
    end = MPI_Wtime();
    task_id++;
    Task task_stacking= Task("rtm", "stacking",task_id );
    vector<string> transformation_tags = {"runrtm"};
    task_stacking.add_dependent_transformation_tags(transformation_tags);
    task_stacking.add_dependent_transformation_id(task_runrtm.get_id());


    vector<string> ostacking_values = {stackedFile_02, stackedLaplacianFile_02, std::to_string(end-start)};
    Dataset& ds_ostacking = task_stacking.add_dataset("ostacking");
    ds_ostacking.add_element_with_values(ostacking_values);
    task_stacking.begin();

    task_stacking.end();       
        
//	+++ Free memory +++
	free(velocityModel);                       velocityModel = NULL;
    free(stackSelfCorrelation);                stackSelfCorrelation = NULL;
    free(stackCrossCorrelation);               stackCrossCorrelation = NULL;
    free(stackCrossCorrelationLaplacian);      stackCrossCorrelationLaplacian = NULL;
    free(modifiedVelocityModel);               modifiedVelocityModel = NULL;
    free(shotLocation);                        shotLocation = NULL;
    free(seismogram);                          seismogram = NULL;
	free(wavelet);                             wavelet = NULL;
}
