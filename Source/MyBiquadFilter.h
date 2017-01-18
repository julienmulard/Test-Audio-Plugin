#pragma once
#include <cmath>
#include <complex>
#include "MyFilter.h"
# define M_PI           3.14159265358979323846  /* pi */

class MyBiquadFilter: public MyFilter
{
public:
	MyBiquadFilter(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);

	~MyBiquadFilter();

	virtual void setCutoff(float cutoff) override;
	virtual void setQ(float Q);
	virtual void setFilter(float cutoff, float Q) override;

	virtual void setSampleRate(float sampleRate) override;

	float filter(float input);

	float getFrequencyResponse(float f, int order = 1) override;

protected:
	//The filter parameters
	float mQ;

	//The filter coefficients used to compute the output
	float mA[3];
	float mB[3];

	//Computation values
	float m1_Fs;
	float m1_Q;
	float mW0;
	float mS0;
	float mC0;
	float mAlpha;

	//Memories for the actual filtering
	float mMemIn[2];
	float mMemOut[2];

	//Methods
	virtual void mComputeFilterCoefficients() =0;
	

};
