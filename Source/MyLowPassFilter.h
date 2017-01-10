#pragma once

#include "MyFilter.h"

class MyLowPassFilter : public MyFilter
{
public:
	MyLowPassFilter(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyLowPassFilter();

private:

	void mComputeFilterCoefficients() override;

};