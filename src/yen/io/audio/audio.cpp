#include "yen/io/audio/audio.hpp"


Audio::Audio(std::shared_ptr<Config> config, std::shared_ptr<State> state)
  : state(state)
{
  
  if ( dac.getDeviceCount() < 1 ) {
    std::cout << "\nNo audio devices found!\n";
    exit( 0 );
  }

  parameters.deviceId = dac.getDefaultOutputDevice();
  parameters.nChannels = 2;
  parameters.firstChannel = 0;
  sampleRate = 44100;
  bufferFrames = 256; // 256 sample frames
  // double data[2];

}

void Audio::connect() {  
  try {
    dac.openStream( &parameters,
                    NULL,
                    RTAUDIO_FLOAT64,
                    sampleRate,
                    &bufferFrames,
                    this->callback,
                    this );
    dac.startStream();
  }
  catch ( RtAudioError& e ) {
    e.printMessage();
    exit( 0 );
  }

  // char input;
  // std::cout << "\nPlaying ... press <enter> to quit.\n";
  // std::cin.get( input );
  // try {
  //   // Stop the stream
  //   dac.stopStream();
  // }
  // catch (RtAudioError& e) {
  //   e.printMessage();
  // }
  // if ( dac.isStreamOpen() ) dac.closeStream();
}

int Audio::callback( void *outputBuffer,
                     void *inputBuffer,
                     unsigned int nBufferFrames,
                     double streamTime,
                     RtAudioStreamStatus status,
                     void *userData )
{
  double *buffer = (double *) outputBuffer;
  
  // get state
  auto this_audio = (Audio *)(userData);
  auto state = this_audio->state;

  // get playing samples
  std::vector< std::shared_ptr<Sample> > samples;
  for (auto sample : state->samples->samples) {
    if (sample->is_playing) samples.push_back(sample);
  }

  // iterate over buffer frames
  for (unsigned int i = 0; i < nBufferFrames; i++) {
    // since we are using 2-channel audio, lets write interleaved audio data for each channel
    for (unsigned int channel = 0; channel < 2; channel++) {
      double frame_value = 0;
      
      // iterate over playing samples
      for (auto sample : samples) {
        // get current frame from sample and add to frame_value
        frame_value += sample->get_frame(channel);
      }

      // set the buffer frame value for this channel
      *buffer++ = frame_value;
    }
  }
  
  // do audio stuff
  
  return 0;
}
