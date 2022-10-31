#include <math.h>
#include "pav_analysis.h"

#define SIGN(x) ((x > 0) ? 1 : ((x < 0) ? -1 : 0))

float compute_power(const float *x, unsigned int N) {
    //potencia
    float power=1.0e-12f;

    for (int i=0; i<N; i++){
        power=power+x[i]*x[i];
    }
    
    return 10*log10f(power/ (float)N);
}

float compute_am(const float *x, unsigned int N) {
    //amplitud media
    float am = 0.0f;

    for(int i=0; i<N; i++){
        am = am + fabsf(x[i]);
    }

    return (am/(float)N);
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    //tasa de cruce por cero 
    float zcr = 0.0f;
    const float c = fm/((float)2*(N-1));

    for(int i=0; i<N; i++){
        if(SIGN(x[i])!=SIGN(x[i-1])){
            zcr++;
        }    
    }
    return c*zcr;
}