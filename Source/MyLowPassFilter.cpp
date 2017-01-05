#include "MyLowPassFilter.h"

MyLowPassFilter::MyLowPassFilter()
{
	mSampleRate = 44100.0;
	mCutoffFrequency = 22050.0;
	mQ = 0;

	m1_Fs = 1 / mSampleRate;

	mComputeFilterCoefficients();

	mMemIn[0] = 0.0;
	mMemIn[1] = 0.0;
	mMemOut[0] = 0.0;
	mMemOut[2] = 0.0;
}

MyLowPassFilter::~MyLowPassFilter()
{

}

MyLowPassFilter::MyLowPassFilter(float cutoff, float Q, float sampleRate)
{
	mSampleRate = sampleRate;
	mCutoffFrequency = cutoff;
	mQ = Q;

	m1_Fs = 1 / mSampleRate;
	m1_Q = 1 / mQ;

	mComputeFilterCoefficients();
}


void MyLowPassFilter::setCutoff(float cutoff)
{
	mCutoffFrequency = cutoff;
	mComputeFilterCoefficients();
}

void MyLowPassFilter::setQ(float Q)
{
	mQ = Q;
	m1_Q = 1.0f / mQ;
	mComputeFilterCoefficients();
}

void MyLowPassFilter::setFilter(float cutoff, float Q)
{
	mCutoffFrequency = cutoff;
	mQ = Q;
	m1_Q = 1.0f / mQ;
	mComputeFilterCoefficients();
}


void MyLowPassFilter::setSampleRate(float sampleRate)
{
	mSampleRate = sampleRate;
	m1_Fs = 1.0f / mSampleRate;
	mComputeFilterCoefficients();
}

void MyLowPassFilter::mComputeFilterCoefficients()
{
	mW0 = 2.0f * float(M_PI) * mCutoffFrequency * m1_Fs;

	mC0 = cos(mW0);
	mS0 = sin(mW0);

	mAlpha = 0.5 * mS0 * m1_Q;

	mB[0] = (1.0f - mC0) * 0.5f;
	mB[1] = 1.0f - mC0;
	mB[2] = (1.0f - mC0) * 0.5f;
	mA[0] = 1.0f + mAlpha;
	mA[1] = -2.0f * mC0;
	mA[2] = 1.0f - mAlpha;
}


float MyLowPassFilter::filter(float input) 
{
	float output = (mB[0] * input + mB[1] * mMemIn[0] + mB[2] * mMemIn[1] - mA[1] * mMemOut[0] - mA[2] * mMemOut[1]) / mA[0]+10e-20;

	mMemIn[1] = mMemIn[0];
	mMemIn[0] = input;

	mMemOut[1] = mMemOut[0];
	mMemOut[0] = output;

	return output;
}

