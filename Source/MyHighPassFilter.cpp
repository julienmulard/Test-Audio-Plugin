#include "MyHighPassFilter.h"


#include "MyHighPassFilter.h"

MyHighPassFilter::MyHighPassFilter(float cutoff, float Q, float sampleRate) : MyFilter(cutoff, Q, sampleRate) {

}

MyHighPassFilter::~MyHighPassFilter() {

}


void MyHighPassFilter::mComputeFilterCoefficients()
{
	mW0 = 2.0f * float(M_PI) * mCutoffFrequency * m1_Fs;

	mC0 = cos(mW0);
	mS0 = sin(mW0);

	mAlpha = 0.5f * mS0 * m1_Q;

	mB[0] = (1.0f + mC0) * 0.5f;
	mB[1] = -1.0f - mC0;
	mB[2] = (1.0f + mC0) * 0.5f;
	mA[0] = 1.0f + mAlpha;
	mA[1] = -2.0f * mC0;
	mA[2] = 1.0f - mAlpha;
}




