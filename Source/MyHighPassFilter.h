#pragma once

#include "MyFilter.h"

class MyHighPassFilter : public MyFilter
{
public:
	MyHighPassFilter(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyHighPassFilter();

private:

	void mComputeFilterCoefficients() override;

};