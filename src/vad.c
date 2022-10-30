#include <math.h>
#include <stdlib.h>
#include <stdio.h>

#include "vad.h"
#include "pav_analysis.h"

const float FRAME_TIME = 10.0F; /* in ms. */
unsigned int cnt_mb_voice = 0; /*contador tramas en mb_voice*/
unsigned int cnt_mb_silence = 0;  /*contador tramas en mb_silence*/
unsigned int cnt_th_init = 0; /*contador tramas para threshold en init*/
const float fm = 16000;

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
 * TODO: Delete and use your own features!
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
  //Utilizando las funciones de analysis.c podemos obtener los parametros deseados
  //para asi poder marcar lindares que nos dara informacion de en que situación nos encontramos
  feat.zcr=compute_zcr(x,N,fm); 
  feat.p=compute_power(x,N);
  feat.am=compute_am(x,N);

  return feat;
  
}

/* 
 * TODO: Init the values of vad_data
 */

VAD_DATA * vad_open(float rate, float alfa1, float alfa2) {  
  VAD_DATA *vad_data = malloc(sizeof(VAD_DATA));
  vad_data->state = ST_INIT;
  vad_data->sampling_rate = rate;
  vad_data->frame_length = rate * FRAME_TIME * 1e-3;
  vad_data->alfa1 = alfa1;
  vad_data->alfa2 = alfa2;
  vad_data->counter = 0;
  vad_data->MAX_MB = 5;           //Mirar aquestes avriables i buscar "les nostres propies"
  vad_data->MIN_VOICE = 30;
  vad_data->MIN_SILENCE = 10;
  vad_data->N_TRAMAS = 3;

  return vad_data;
}

VAD_STATE vad_close(VAD_DATA *vad_data) {
  /* 
   * DONE: decide what to do with the last undecided frames
   */
  VAD_STATE state = vad_data->state;  //-->>>mirar si acaba con le anterior o siempre com silencio
  free(vad_data);
  return state;
}

unsigned int vad_frame_size(VAD_DATA *vad_data) {
  return vad_data->frame_length;
}

/* 
 * TODO: Implement the Voice Activity Detection 
 * using a Finite State Automata
 */

VAD_STATE vad(VAD_DATA *vad_data, float *x) {

  /* 
   * TODO: You can change this, using your own features,
   * program finite state automaton, define conditions, etc.
   */

  Features f = compute_features(x, vad_data->frame_length);
  vad_data->last_feature = f.p; /* save feature, in case you want to show */

  switch (vad_data->state) {
  case ST_INIT: 
  
    vad_data->k1  = f.p + vad_data->alfa1-0.5;  // -0.45
    vad_data->k2  = f.p + vad_data->alfa2 +7.61;  // +7.5
    vad_data->state = ST_SILENCE;

      /*
      printf("El nivel k0 es %f\n", vad_data->k0);
      printf("El nivel k1 es %f\n", vad_data->k1);
      printf("El nivel k2 es %f\n", vad_data->k2);
      printf("El valor de number_init introducido es: %d\n", vad_data->counter_init);
      printf("El valor de number_ms introducido es: %d\n", vad_data->counter_ms);
      printf("El valor de number_mv introducido es: %d\n", vad_data->counter_mv);
      printf("El valor de alpha1 introducido es: %f\n", vad_data->alpha1);
      printf("El valor de alpha2 introducido es: %f\n", vad_data->alpha2);
      */
    break;

  case ST_SILENCE:
    //printf("ZCR en S: %f\n", f.zcr);
    if (f.p > vad_data->k1){
      vad_data->state = ST_MV;
      //printf("De S me voy a MV\n");
    }
    break;

  case ST_VOICE:
    //printf("ZCR en V: %f\n", f.zcr);
    if (f.p < vad_data->k2){
      vad_data->state = ST_MS;
      //printf("De V me voy a MS\n");
    }
    break;

    case ST_MV:
    //printf("Llevo %u tramas en MV\n", vad_data->counter_N);
    //printf("ZCR en MV: %f\n", f.zcr);
    if(f.p > vad_data->k2 && vad_data->counter_N < vad_data->counter_mv){
      vad_data->state = ST_VOICE;
      vad_data->counter_N = 0;
      //printf("De MV me voy a V\n");
    }else if(vad_data->counter_N == vad_data->counter_mv){
      //printf("He llegado al máximo de MV\n");
      vad_data->state = ST_SILENCE;
      vad_data->counter_N = 0;
      //printf("De MV me voy a S\n");
    }else{
      vad_data->counter_N ++;
      //printf("Sigo MV\n");
    }
    break;

  case ST_MS:
    //printf("Llevo %u tramas en MS\n", vad_data->counter_N);
    //printf("ZCR en MS: %f\n", f.zcr);
    if(f.p > vad_data->k2 && vad_data->counter_N < vad_data->counter_ms){
      vad_data->state = ST_VOICE;
      vad_data->counter_N = 0;
      //printf("De MS me voy a V\n");
    }else if(vad_data->counter_N == vad_data->counter_ms){
      //printf("He llegado al máximo de MS\n");
      vad_data->state = ST_SILENCE;
      vad_data->counter_N = 0;
      //printf("De MS me voy a S\n");
    }else {
      vad_data->counter_N ++;
      //printf("Sigo MS\n");
    }
    break;

  case ST_UNDEF:
    break;
  }

  if (vad_data->state == ST_SILENCE ||
      vad_data->state == ST_VOICE)
    return vad_data->state;
  else
    return ST_UNDEF;
}

void vad_show_state(const VAD_DATA *vad_data, FILE *out) {
  fprintf(out, "%d\t%f\n", vad_data->state, vad_data->last_feature);
}
