#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
  
   float Pot=1.0e-9f ;

   for (int i = 0; i < N; i++){
    Pot=Pot + ( x[i]*x[i]);
   }
    return 10*log10(Pot/(float)N);
   
   
}

float compute_am(const float *x, unsigned int N) {
    
float Amp=0;

for (int i = 0; i < N; i++)
{
  Amp=Amp+fabs(x[i]);
}
    return Amp/N;
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