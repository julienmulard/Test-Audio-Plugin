#pragma once
#include <cmath>
# define M_PI           3.14159265358979323846  /* pi */

class MyLowPassFilter
{
public:
	MyLowPassFilter();
	MyLowPassFilter (float cutoff, float Q, float sampleRate)
	
	~MyLowPassFilter();

	void setCutoff(float cutoff);
	void setQ(float Q);
	void setFilter(float cutoff, float Q);


private:
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
	

	//Methods
	void mComputeFilterCoefficients();

};