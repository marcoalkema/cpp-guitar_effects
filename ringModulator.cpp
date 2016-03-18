#include "ringModulator.h"

float mod_phase=0;

void RingModulator::setFs(float Fs){
  this->Fs = Fs;
}

void RingModulator::setFc(float Fc){
  this->Fc = Fc;
}

//processing samples
void RingModulator::process_samples(float *inputbuffer, float *outputbuffer)
{
 
  if (bypass == 1) {
    for(int bufptr=0; bufptr<FRAMESPERBUFFER; bufptr++) {
      outputbuffer[bufptr] = inputbuffer[bufptr];
    }
  }
  else {
    for(int bufptr=0; bufptr<FRAMESPERBUFFER; bufptr++) {
      // inputbuffer[bufptr] = sin(2*M_PI*inputbuffer[bufptr]*(Fc/Fs)); //
      // outputbuffer[bufptr] = 0.5 * inputbuffer[bufptr]; // Ring modulation
      // outputbuffer[bufptr] = inputbuffer[bufptr];

      outputbuffer[bufptr]= 0.005 * inputbuffer[bufptr] * (1 + Fs*sin(mod_phase) );
      mod_phase+=Fc*2*M_PI/SAMPLERATE;
    }
  }
}
