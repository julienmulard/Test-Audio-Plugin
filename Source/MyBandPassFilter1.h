#pragma once

#include "MyBiquadFilter.h"

class MyBandPassFilter1 : public MyBiquadFilter
{
public:
	MyBandPassFilter1(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyBandPassFilter1();

private:

	void mComputeFilterCoefficients() override;

};
