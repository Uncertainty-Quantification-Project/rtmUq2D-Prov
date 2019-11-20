#ifndef BACKWARD_MODELING_H
#define BACKWARD_MODELING_H

void adjointModeling(int simId, int *shot, float *velocity, float *wavelet, float *seismogram, float *imageCondition, float *selfImageCondition);

#endif