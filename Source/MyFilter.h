#pragma once
#include <cmath>
# define M_PI           3.14159265358979323846  /* pi */

class MyFilter
{
public:
	MyFilter(float cutoff = 1000.0f, float Q = 0.5f, float sampleRate = 44100.0f);

	~MyFilter();

	void setCutoff(float cutoff);
	void setQ(float Q);
	void setFilter(float cutoff, float Q);

	void setSampleRate(float sampleRate);

	float filter(float input);

protected:
	//The filter parameters
	float mSampleRate;
	float mCutoffFrequency;
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
	virtual void mComputeFilterCoefficients();

};
