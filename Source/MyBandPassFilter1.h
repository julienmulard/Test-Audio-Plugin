#pragma once

#include "MyFilter.h"

class MyBandPassFilter1 : public MyFilter
{
public:
	MyBandPassFilter1(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);
	~MyBandPassFilter1();

private:

	void mComputeFilterCoefficients() override;

};
