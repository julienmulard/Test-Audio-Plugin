#pragma once

#include "..\JuceLibraryCode\JuceHeader.h"

class FrequencyResponseDisplay: public Component
{
public:
	FrequencyResponseDisplay();
	~FrequencyResponseDisplay();

	void setFilterResponsePath(Array<float> frequencies, Array<float> amplitudes);

private:
	Path filterResponse;

	void paint(Graphics &g) override;
	
};

