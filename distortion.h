#include "effect.h"
#include <math.h>
#include <complex.h>
#include <iostream>



class Distortion : public Effect
{
public:
  void setTimbre(float timbre);
  void setDepth(float depth);
  void process_samples(float *inputbuffer, float *outputbuffer);

  float timbre = 1;
  float timbreInverse;
  float depth = 1;
  int bypass = 1;

private:

}; // distortion
