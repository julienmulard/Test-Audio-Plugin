#pragma once

#include "MyBiquadFilter.h"

class MyNotchFilter : public MyBiquadFilter
{
public:
	MyNotchFilter(float cutoff = 1000.0f, float Q=0.5f, float sampleRate = 44100.0f);
	~MyNotchFilter();

private:

	void mComputeFilterCoefficients() override;

};

