#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"

class FrequencyResponseDisplay: public Component
{
public:
	FrequencyResponseDisplay();
	~FrequencyResponseDisplay();

	void setFilterResponsePath(Array<float> frequencies, Array<float> amplitudes, float cutoff);

private:
	Path filterResponse;
	float mXCutoff;

	void paint(Graphics &g) override;
	
};

