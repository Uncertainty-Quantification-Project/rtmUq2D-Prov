#ifndef STENCILDFM_H
#define STENCILDFM_H

// Half of discretization order for FDM (order/2)
#define HALFORDERDF 4

// Second Convolutional's derivative coefficients 8 order
#define AC08 -2.97399944f
#define AC18 +1.70507669f
#define AC28 -0.25861812f
#define AC38 +0.04577745f
#define AC48 -0.00523630f


void iso_acoustic_wave_equation(float *pond, float *waveField2, float *waveField3);


#endif
