#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "pav_analysis.h"
#include "vad.h"
#include "pav_analysis.h"
#include "vad.h"


const float FRAME_TIME = 10.0F; /* in ms. */
unsigned int NThrIni = 0; //counter de tramas para el lindar en INIT
unsigned int NMaybeVoice = 0; //counter de tramas de maybe_voice
unsigned int cnt_mb_silence = 0;  //counter de tramas maybe_silence
float accum_power = 0; //variable que acumula potencia del inicio
const float fm = 16000; //frecuencia de muestreo 
/* 
 * As the output state is only ST_VOICE, ST_SILENCE, or ST_UNDEF,
 * only this labels are needed. You need to add all labels, in case
 * you want to print the internal state in string format
 */

const char *state_str[] = {
  "UNDEF", "S", "V", "INIT"
};

const char *state2str(VAD_STATE st) {
  return state_str[st];
}

/* Define a datatype with interesting features */
typedef struct {
  float zcr;
  float p;
  float am;
} Features;

/* 
 * DONE: Delete and use your own features!
 */

Features compute_features(const float *x, int N) {
  /*
   * Input: x[i] : i=0 .... N-1 
   * Ouput: computed features
   */
  /* 
   * DELETE and include a call to your own functions
   *
   * For the moment, compute random value between 0 and 1 
   */
  Features feat;
  
  feat.p=compute_power(x, N);
  feat.zcr = compute_zcr(x, N, fm);
  feat.am=compute_am(x, N);

  return feat;
}

/* 
 * DONE: Init the values of vad_data
 */

VAD_DATA * vad_open(float rate, float alfa1) {
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->state = ST_INIT;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
<<<<<<< HEAD
/*<<<<<<< HEAD
  vad_data->alfa1 = alfa1;
  vad_data->alfa2 = alfa2;
  vad_data->counter_N = 0;
  vad_data->MAX_MB = 5;           //Mirar aquestes avriables i buscar "les nostres propies"
  vad_data->MIN_VOICE = 30;
  vad_data->MIN_SILENCE = 10;
 
=======*/
  vad_data->alpha1=alpha1;
=======
  vad_data->alfa1=alfa1;
>>>>>>> 1a2b3342a870f14c55b676632522fba02d53b5c4
  vad_data->k0 = 5; 
  vad_data->k1 = 5;
  vad_data->trigger_INIT = 0.99; //marcamos el trigger 0.989
  vad_data->NumInitStable = 5; 
  vad_data->NumVoiceStable = 0;
  vad_data->NumSilenceStable = 8; 

  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  /* 
   * TODO: decide what to do with the last undecided frames
   */
  VAD_STATE state = ST_SILENCE; 
  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}

/* 
 * DONE: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x) {

  /* 
   * DONE: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state) {
/*<<<<<<< HEAD
  case ST_INIT: 
  
    vad_data->k1  = f.p + vad_data->alfa1-0.5;  // -0.45
    vad_data->k2  = f.p + vad_data->alfa2 +7.61;  // +7.5
    vad_data->state = ST_SILENCE;

      /*
      /Chivatos para comprobar los valores 
      printf("El nivel k1 es %f\n", vad_data->k1);
      printf("El nivel k2 es %f\n", vad_data->k2);
      printf("El valor de alpha1 introducido es: %f\n", vad_data->alfa1);
      printf("El valor de alpha2 introducido es: %f\n", vad_data->alfa2);
      
    
    break;

  case ST_SILENCE:
    printf("ZCR en S: %f\n", f.zcr);
    if (f.p > vad_data->k2){
      vad_data->state = ST_MV;
      printf("De S me voy a MV\n");
    }else if(f.p > vad_data->k1){
      vad_data->N_TRAMAS --;
      vad_data->state = ST_MS;
      printf("De S me voy a MS\n");
      
    }
    break;

  case ST_VOICE:
    printf("ZCR en V: %f\n", f.zcr);
    if (f.p < vad_data->k1){
      vad_data->state = ST_MS;
      printf("De V me voy a MS\n");
    }else if(f.p < vad_data->k2){
      vad_data->state = ST_MV;
      printf("De V me voy a MV\n");
    }
    break;

  case ST_MV:
    printf("Llevo %u tramas en MV\n", vad_data->counter_N);
    printf("ZCR en MV: %f\n", f.zcr);
    if(f.p > vad_data->k2 ){
      vad_data->state = ST_VOICE;
      printf("De MV me voy a V\n");
    }else if(f.p < vad_data->k1 ||vad_data->N_TRAMAS==0){
      printf("He llegado al máximo de MV\n");
      vad_data->state = ST_SILENCE;
      vad_data->N_TRAMAS= 3;
      printf("De MV me voy a S\n");
    }else{
      vad_data->N_TRAMAS--;
      printf("Sigo MV\n");
    }
    break;

  case ST_MS:
    printf("Llevo %u tramas en MS\n", vad_data->counter_N);
    printf("ZCR en MS: %f\n", f.zcr);
    if(f.p > vad_data->k2 ||vad_data->N_TRAMAS==0){
      vad_data->state = ST_VOICE;
      vad_data->N_TRAMAS = 3;
      printf("De MS me voy a V\n");
    }else if(f.p < vad_data->k1){
      printf("He llegado al máximo de MS\n");
      vad_data->state = ST_SILENCE;
      printf("De MS me voy a S\n");
    }else {
      vad_data->N_TRAMAS--;
      printf("Sigo MS\n");
    }
=======*/
  case ST_INIT:
    accum_power = f.p + accum_power;  
    NThrIni++;
    if(f.p >= (accum_power/NThrIni)*(vad_data->trigger_INIT) && (vad_data->NumInitStable < NThrIni)){ 
      vad_data-> p1 = vad_data->k0 + (accum_power/NThrIni); 
      vad_data->state = ST_SILENCE; 
      NThrIni = 0;
    }
    break;

  case ST_MAYBE_VOICE:
    if (f.p >= vad_data->p1 + vad_data->k1){
      if(NMaybeVoice >= vad_data->NumVoiceStable){
        vad_data->state = ST_VOICE;
        NMaybeVoice = 0;
      }else{
        NMaybeVoice++;
      }
    }else
     vad_data->state = ST_SILENCE;

    break;

  case ST_MAYBE_SILENCE:
    if (f.p <= vad_data->p1){ 
      if(cnt_mb_silence >= vad_data->NumSilenceStable){
      vad_data->state = ST_SILENCE;
      cnt_mb_silence = 0;
      }else{
        cnt_mb_silence++;
      }
    }else if(f.p > vad_data->p1)
      vad_data->state = ST_VOICE;
    break;

  case ST_SILENCE:
    if (f.p > vad_data->p1)
      vad_data->state = ST_MAYBE_VOICE;

    break;

  case ST_VOICE:
    if (f.p < vad_data->p1)
      vad_data->state = ST_MAYBE_SILENCE;
    break;

  case ST_UNDEF:
    printf("Hem entrat a undef");
    break;

  }

/*<<<<<<< HEAD
  if (vad_data->state == ST_SILENCE ||vad_data->state == ST_MV)
    return ST_SILENCE;
  else if (vad_data->state == ST_VOICE ||vad_data->state == ST_MS)
    return ST_VOICE;
=======*/
  if (vad_data->state == ST_SILENCE ||vad_data->state == ST_VOICE)
    return vad_data->state;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out) {
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
