#pragma once

#include "MyBiquadFilter.h"

class MyLowPassFilter : public MyBiquadFilter
{
public:
	MyLowPassFilter(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyLowPassFilter();

private:

	void mComputeFilterCoefficients() override;

};