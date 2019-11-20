#ifndef FIXED_PARAMETERS_H
#define FIXED_PARAMETERS_H

// >> Obs.: This information can be acessed from any part of the program.


// -------- Input Disk FILES...
static char velocityFile[] = "./INPUTS/marmousi2_30x30_%05d.bin";
static char waveletFile[]  = "./INPUTS/i_ricker.rsf@";
static char seismogramFile[]  = "./INPUTS/seismogram_norm_%05d.bin";
// ----------------------------------

// -------- Temporary FILES...
static char crossCorrelationFile[] = "./TEMPORARY_FILES/crossCorrelation_%05dX%05d.bin";
static char selfSourceCorrelationFile[] = "./TEMPORARY_FILES/selfCrossCorrelation_%05dX%05d.bin";
static char sourceWavefieldFile[] = "./TEMPORARY_FILES/sourceWavefield_%05d.bin";
// ----------------------------------

// -------- Output Disk FILES...
static char stackedFile[] = "./OUTPUTS/stackedBrute_%05d.bin";
static char stackedLaplacianFile[] = "./OUTPUTS/stackedLaplacian_%05d.bin";
// ----------------------------------

// -------- Finite Difference Model Parametrization...
static const float spacingGrid 	= 6.25;		// Define the value in meter from one grid point to the next one.
static const float sampling 	= 0.0005;	// Define the value in seconds from one sample to the nexto one.
// ----------------------------------

// Total number of simulations...
static const int numberOfSimulations = 1;

// -------- Dimension of the MODEL...
static const int Nx			= 2721;
static const int Nz			= 561;
// ----------------------------------


// -------- Information of the SHOT...
static const int firstLocationShot	= 5;
static const int depthShot		= 5;
static const int spacingShot		= 17;
static const int numberOfShots	        = 2;
// ---------------------------------- ++ Shot distribuition will be build based on arithmietic progression ++


// -------- Information of the RECEIVERS...
static const int firstLocationReceiver  = 1;
static const int depthReceiver	        = 5;
static const int spacingReceiver	= 3;
static const int numberOfReceivers	= 1361;
// ---------------------------------- ++ Receiver distribuition will be build based on arithmietic progression ++


// -------- Information of the step time of the ACQUISITION...
static const int numberOfTimeStep 	= 14000;
// ----------------------------------

// -------- Information of the WAVELET...
static const int sampligWavelet 	= 800;
static const float cutFrequency 	= 50.0;
// ----------------------------------



// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// Please, it do not modify the Absorbing Layers Thickness

// -------- Absorbing Layers Thickness...
static const int thicknessUp 	= 50;
static const int thicknessDown 	= 50;
static const int thicknessLeft 	= 50;
static const int thicknessRight = 50;
// ----------------------------------

#endif
