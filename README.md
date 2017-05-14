# Test-Audio-Plugin
A multi-filter with a nice display VST plugin using JUCE.

## Overview
Multiple filters, with adjustable cutoff frequency and quality factor:
- Biquadratic low pass filter
- Biquadratic high pass filter
- Biquadratic notch pass filter
- Biquadratic band pass filter (with and without fixed gain at cutoff)
- Comb filter (note that the quality factor is irrelevant here, but you can modifiy the amount of feedback)

Cascade the same filter up to four times.

Nice display to see things happening in real time!

## How to test it

You can download the vst [here](https://drive.google.com/open?id=0B0QpOgRYCqN3d2xiem9HSjVrQzg). 

If you have a VST compatible Digital Audio Workstation (DAW), put this in your VST folder (probably something like C:\Program Files(x86)\VstPlugins), refresh your VST list in your DAW and have fun.

If you have no idea of what I am talking about, you can download  [VST Plugin Analyser](http://www.pcjv.de/applications/measurement-programs/) (That's one of the tools I use to debug), load the plugin and observe the frequency response. It's not listening to the thing, but, hey, it's something! 

## Future Evolutions

Adding a LFO and an Enveloppe Detector to make things more dynamic.

## Side Notes
To begin with, I'd like to apologize to all non-french speaking people reading the commit messages, I did not anticipate this kind of issues when I began working on this project (I did not anticipate sharing it on the internet either to be honnest)

Please also note that I started this project as an excuse to write some C++ and do some signal processing. I do not guarantee this plugin works on anything else than my own computer for now, as I don't have the time and means to test this on anything else than Windows8.1/FLStudio 12. 
