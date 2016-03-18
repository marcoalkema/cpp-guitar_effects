#include <iostream>
#include "distortion.h"
#include "delay.h"
#include "ringModulator.h"
#include "lib/osc/osc.h"

using namespace std;

class localOSC : public OSC
{
  //TODO make seperate files for LocalOSC (.h and .cpp)
  //TODO make effect private 
  Effect **effect;

  public:
  void setEffect(Effect **effect) {
    this->effect = effect;
  };
  
  int realcallback(const char *path,const char *types,lo_arg **argv,int argc)
  {
  string msgpath=path;

  

    if(!msgpath.compare("/distortionTimbre")){
      float int1 = argv[0]->f;
      if (effect) {
	static_cast < Distortion *> (effect[0])->setTimbre(int1);
      }
    }

    if(!msgpath.compare("/distortionDepth")){
      float int1 = argv[0]->f;
      if (effect) {
      	static_cast < Distortion *> (effect[0])->setDepth(int1);
      }      
    }

    if(!msgpath.compare("/distortionBypass")){
      int int1 = argv[0]->i;
      if (effect) {
      	static_cast < Distortion *> (effect[0])->bypass = int1;
      }
    }
    
    if(!msgpath.compare("/delayTime")){
      float int1 = argv[0]->f;
      if (effect) {
      	static_cast < Delay *> (effect[1])->setDelayTime(int1);
      }      
    }

    if(!msgpath.compare("/feedback")){
      float int1 = argv[0]->f;
      if (effect) {
      	static_cast < Delay *> (effect[1])->setFeedback(int1);
      }      
    }
    
    if(!msgpath.compare("/delayBypass")){
      int int1 = argv[0]->i;
      if (effect) {
      	static_cast < Delay *> (effect[1])->bypass = int1;
      }      
    }

    
    if(!msgpath.compare("/frequency")){
      float int1 = argv[0]->f;
      if (effect) {
      	static_cast < RingModulator *> (effect[2])->setFc(int1);
      }      
    }
    
    if(!msgpath.compare("/LfoRate")){
      float int1 = argv[0]->f;
      if (effect) {
      	static_cast < RingModulator *> (effect[2])->setFs(int1);
      }      
    }

    if(!msgpath.compare("/RingmBypass")){
      int int1 = argv[0]->i;
      cout << int1 << endl;
      if (effect) {
      	static_cast < RingModulator *> (effect[2])->bypass = int1;
      }      
    }

    return 0;
  } // realcallback()
};


int main()
{

  
localOSC osc;
int done = 0;
string serverport="7777";

int input_device=-1,output_device=-1;
float inputbuffer[FRAMESPERBUFFER*NROFCHANNELS];
float outputbuffer[FRAMESPERBUFFER*NROFCHANNELS];

Effect **effect; 
effect = new Effect* [3];
effect[0]=new Distortion; 
effect[1]=new Delay;
effect[2]=new RingModulator;
//

 osc.setEffect(effect);
 
 osc.init(serverport);
 osc.set_callback("/distortionTimbre","f");
 osc.set_callback("/distortionDepth","f");
 osc.set_callback("/distortionBypass","i");
 osc.set_callback("/delayTime","f");
 osc.set_callback("/feedback","f");
 osc.set_callback("/delayBypass","i");
 osc.set_callback("/frequency","f");
 osc.set_callback("/LfoRate","f");
 osc.set_callback("/RingmBypass","i");
  
 osc.start();


  Audio_IO audiostream;

  // Init Portaudio properties and start the PA-server
  audiostream.set_mode(AUDIO_IO_READWRITE);
  audiostream.set_samplerate(SAMPLERATE);
  audiostream.set_nrofchannels(NROFCHANNELS);
  audiostream.set_framesperbuffer(FRAMESPERBUFFER);
  audiostream.initialise();

  audiostream.list_devices();
  cout << "\nGive input device number: ";
  cin >> input_device;
  audiostream.set_input_device(input_device);
  cout << "Give output device number: ";
  cin >> output_device;
  audiostream.set_output_device(output_device);

  audiostream.start_server();
  


  
  while(1) {
    int n=0;
    audiostream.read(inputbuffer);
    
    effect[n++]->process_samples(inputbuffer,outputbuffer);
    effect[n++]->process_samples(outputbuffer,inputbuffer);
    effect[n++]->process_samples(inputbuffer,outputbuffer);
    audiostream.write(outputbuffer);
  } // while

  audiostream.finalise();
} // main()

