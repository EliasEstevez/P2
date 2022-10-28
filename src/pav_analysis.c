#include <math.h>
#include "pav_analysis.h"
<<<<<<< HEAD
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

=======



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
>>>>>>> 0a300a8407aabcb8beab878b9c48fe2df1c1acf5
