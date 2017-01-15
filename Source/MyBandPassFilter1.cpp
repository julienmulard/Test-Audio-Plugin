#include "MyBandPassFilter1.h"


MyBandPassFilter1::MyBandPassFilter1(float cutoff, float Q, float sampleRate) : MyBiquadFilter(cutoff, Q, sampleRate) {
	mComputeFilterCoefficients();
}

MyBandPassFilter1::~MyBandPassFilter1() {

}

void MyBandPassFilter1::mComputeFilterCoefficients()
{
	mW0 = 2.0f * float(M_PI) * mCutoffFrequency * m1_Fs;

	mC0 = cos(mW0);
	mS0 = sin(mW0);

	mAlpha = 0.5f * mS0 * m1_Q;

	mB[0] = mS0 * 0.5f;
	mB[1] = 0;
	mB[2] = -mS0 * 0.5f;
	mA[0] = 1.0f + mAlpha;
	mA[1] = -2.0f * mC0;
	mA[2] = 1.0f - mAlpha;

		//b0 = sin(w0) / 2 = Q*alpha
		//b1 = 0
		//b2 = -sin(w0) / 2 = -Q*alpha
		//a0 = 1 + alpha
		//a1 = -2 * cos(w0)
		//a2 = 1 - alpha
}

