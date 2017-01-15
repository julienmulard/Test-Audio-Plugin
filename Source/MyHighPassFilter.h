#pragma once

#include "MyBiquadFilter.h"

class MyHighPassFilter : public MyBiquadFilter
{
public:
	MyHighPassFilter(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyHighPassFilter();

private:

	void mComputeFilterCoefficients() override;

};