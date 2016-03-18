#ifndef _EFFECT_H_
#define _EFFECT_H_

#include "lib/audio_IO/audio_io.h"

#define SAMPLERATE		44100
#define NROFCHANNELS		1
#define FRAMESPERBUFFER		256


class Effect
{
public:
  Effect(); // constructor for base class
  virtual ~Effect(); // destructor for base class
  virtual void process_samples(float *inputbuffer,float *outputbuffer);
private:
  unsigned long framesperbuffer;
};

#endif // _EFFECT_H_

