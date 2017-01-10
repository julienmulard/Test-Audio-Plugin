#include "MyNotchFilter.h"

MyNotchFilter::MyNotchFilter(float cutoff, float Q, float sampleRate) : MyFilter(cutoff, Q, sampleRate) {

}

MyNotchFilter::~MyNotchFilter() {

}

void MyNotchFilter::mComputeFilterCoefficients()
{
	mW0 = 2.0f * float(M_PI) * mCutoffFrequency * m1_Fs;

	mC0 = cos(mW0);
	mS0 = sin(mW0);

	mAlpha = 0.5f * mS0 * m1_Q;

	mB[0] = 1.0f;
	mB[1] = -2 * mC0;
	mB[2] = 1.0f;
	mA[0] = 1.0f + mAlpha;
	mA[1] = -2.0f * mC0;
	mA[2] = 1.0f - mAlpha;


		//b0 = 1
		//b1 = -2 * cos(w0)
		//b2 = 1
		//a0 = 1 + alpha
		//a1 = -2 * cos(w0)
		//a2 = 1 - alpha
}