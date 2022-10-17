#include <math.h>
#include "pav_analysis.h"

int i;
float var,y;
float compute_power(const float *x, unsigned int N) {
    var=0;
    for(i=0; i<N; i++)
        var=var+x[i]*x[i];
    return 10*log10(var / N);
}

float compute_am(const float *x, unsigned int N) {
    var=0;
    for(i=0; i<N; i++)
        var=var+fabsf(x[i]);
    return var/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    var=0;
    for(i=1; i<N; i++){
        if((x[i-1])>0 && (x[i])>0 || (x[i-1])<0 && (x[i])<0 || (x[i-1])==0 && (x[i])==0 )
            var=var+1;
    }
    return fm*(var/(N-1))/2;
}
