#include <math.h>
#include "pav_analysis.h"



float compute_power(const float *x, unsigned int N) {
    float p= 1e-12;

    for(int i=0; i<N; i++) {
        p += x[i]*x[i];
    } 
    
    return 10*log10(p/N);
}

float compute_am(const float *x, unsigned int N) {
    float a = 0;

    for (int i = 0; i < N; i++) {
        a += fabsf(x[i]);
    }

    return a/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    float zcr=0;
    for(int i=1; i<N; i++){
        if((x[i-1])>0 && (x[i])>0 || (x[i-1])<0 && (x[i])<0 || (x[i-1])==0 && (x[i])==0 )
            zcr=zcr+1;
    }
    return fm*(zcr/(N-1))/2;
}
