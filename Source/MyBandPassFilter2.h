#pragma once

#include "MyBiquadFilter.h"

class MyBandPassFilter2 : public MyBiquadFilter
{
public:
	MyBandPassFilter2(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyBandPassFilter2();

private:

	void mComputeFilterCoefficients() override;

};

