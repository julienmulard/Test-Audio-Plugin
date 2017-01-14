#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"
#include "FrequencyResponseDisplay.h"

class SpectrumDisplay : public Component
{
public:
	SpectrumDisplay(float min_freq = 20, float max_freq = 22000, float min_gain = -40, float max_gain = 20);
	~SpectrumDisplay();

	void setFilterResponsePath(Array<float> frequencies, Array<float> amplitudes, float cutoff);
	
	void paint(Graphics &g) override;
	void resized() override;

private:
	
	float mMin_freq;
	float mMax_freq;
	float mMin_amp;
	float mMax_amp;

	FrequencyResponseDisplay frequencyResponseDisplay;
		
	//Path filterResponse;

	


};