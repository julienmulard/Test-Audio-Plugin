#include "MyBiquadFilter.h"

MyBiquadFilter::MyBiquadFilter(float cutoff, float Q, float sampleRate):
	MyFilter(cutoff, sampleRate)
{
	mQ = Q;

	m1_Fs = 1 / mSampleRate;
	m1_Q = 1 / mQ;

	//mComputeFilterCoefficients();

	mMemIn[0] = 0.0f;
	mMemIn[1] = 0.0f;
	mMemOut[0] = 0.0f;
	mMemOut[1] = 0.0f;
}

MyBiquadFilter::~MyBiquadFilter()
{

}

void MyBiquadFilter::setCutoff(float cutoff)
{
	mCutoffFrequency = cutoff;
	mComputeFilterCoefficients();
}

void MyBiquadFilter::setQ(float Q)
{
	mQ = Q;
	m1_Q = 1.0f / mQ;
	mComputeFilterCoefficients();
}

void MyBiquadFilter::setFilter(float cutoff, float Q)
{
	mCutoffFrequency = cutoff;
	mQ = Q;
	m1_Q = 1.0f / mQ;
	mComputeFilterCoefficients();
}


void MyBiquadFilter::setSampleRate(float sampleRate)
{
	mSampleRate = sampleRate;
	m1_Fs = 1.0f / mSampleRate;
	mComputeFilterCoefficients();
}

//void MyBiquadFilter::mComputeFilterCoefficients()
//{
//	mW0 = 2.0f * float(M_PI) * mCutoffFrequency * m1_Fs;
//
//	mC0 = cos(mW0);
//	mS0 = sin(mW0);
//
//	mAlpha = 0.5f * mS0 * m1_Q;
//
//	mB[0] = (1.0f - mC0) * 0.5f;
//	mB[1] = 1.0f - mC0;
//	mB[2] = (1.0f - mC0) * 0.5f;
//	mA[0] = 1.0f + mAlpha;
//	mA[1] = -2.0f * mC0;
//	mA[2] = 1.0f - mAlpha;
//}


float MyBiquadFilter::filter(float input)
{
	float output = (mB[0] * input + mB[1] * mMemIn[0] + mB[2] * mMemIn[1] - mA[1] * mMemOut[0] - mA[2] * mMemOut[1]) / mA[0] + 10e-20f;

	mMemIn[1] = mMemIn[0];
	mMemIn[0] = input;

	mMemOut[1] = mMemOut[0];
	mMemOut[0] = output;

	return output;
}

float MyBiquadFilter::getFrequencyResponse(float f, int order) {
	std::complex<float> z(cos(2 * M_PI*f * m1_Fs), sin(2 * M_PI*f * m1_Fs));
	std::complex<float> z2 = z*z;

	std::complex<float> h = (mB[0] * z2 + mB[1] * z + mB[2]) / (mA[0] * z2 + mA[1] * z + mA[2]);

	std::complex<float> hn=h;
	for (int i = 1; i < order; i++) {
		hn = hn*h;
	}
	float abs_hn = std::abs(hn);
	float hn_db = 20 * log10(abs_hn);

	//return 20* std::log10f(std::abs(h));
	return hn_db;

}

