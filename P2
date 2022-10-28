#include <math.h>
#include "pav_analysis.h"
#include <stdlib.h>

float compute_power(const float *x, unsigned int N) {
   float Potencia=0;
   for (int i = 0; i < N; i++){

    Potencia=Potencia + ( x[i]*x[i]);


   }
   float P=10*log10(Potencia/N);
   
   
    return P;
}

float compute_am(const float *x, unsigned int N) {
float Amp=0;

for (int i = 0; i < N; i++)
{
  Amp=Amp+fabs(x[i]);
}
    Amp=Amp/N;
    return Amp;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    
    float zcr=0;
for (int i = 0; i < N; i++)
{
    
    if((((x[i])>0) && (x[i-1]<0)) || (((x[i])<0) && (x[i-1]>0)) )
    {
        zcr++;
    }
}

zcr=(fm*(zcr))/(2*(N-1));
    
    
    return zcr;
}

