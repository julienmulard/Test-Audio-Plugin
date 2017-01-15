#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"

class FrequencyResponseDisplay: public Component
{
public:
	FrequencyResponseDisplay(float min_freq=20, float max_freq=22000, float min_amp=-40, float max_amp=20);
	~FrequencyResponseDisplay();

	void setFilterResponsePath(Array<float> frequencies, Array<float> amplitudes, float cutoff);

private:
	Path filterResponse;
	float mXCutoff;

	float mMin_freq;
	float mMax_freq;
	float mMin_amp;
	float mMax_amp;

	void paint(Graphics &g) override;
	
};

