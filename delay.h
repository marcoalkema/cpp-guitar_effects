#include "effect.h"

#define DELAYBUFFERSIZE 44100

class Delay : public Effect
{
public:
  //functions
  void setDelayTime(float delayTime);
  void setFeedback(float feedback);
  void process_samples(float *inputbuffer, float *outputbuffer);

  float delayBuffer[DELAYBUFFERSIZE];
  int delayTime = 5000;
  int input = 0;
  int output = 0;
  float feedback = 0.5;
  int bypass = 1;

private:

}; // Delay
