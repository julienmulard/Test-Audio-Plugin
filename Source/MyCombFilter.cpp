#include "MyCombFilter.h"

MyCombFilter::MyCombFilter(float cutoff, float feedbackGain, float sampleRate) :MyFilter(cutoff, sampleRate)
{
	mFeedbackGain = feedbackGain;
	
	for (int i = 0; i < mMaxDelay; i++) {
		mDelayLine[i] = 0;
	}

	m1_Fs = 1 / mSampleRate;
	mCurrentPos = 0;
}

MyCombFilter::~MyCombFilter()
{
}

void MyCombFilter::setSampleRate(float sampleRate)
{
	mSampleRate = sampleRate;
	m1_Fs = 1 / mSampleRate;
}

void MyCombFilter::setCutoff(float cutoff)
{
	mCutoffFrequency = cutoff;
	mTauSample = int(mSampleRate/mCutoffFrequency+0.5);

}

void MyCombFilter::setFeedbakcGain(float feedbackGain)
{
	mFeedbackGain = feedbackGain;
}

void MyCombFilter::setFilter(float cutoff, float feedbackGain) 
{
	setCutoff(cutoff);
	setFeedbakcGain(feedbackGain);
}

float MyCombFilter::filter(float input) 
{
	float delayedSample = mDelayLine[mCurrentPos];
	
	float output = input + delayedSample*mFeedbackGain;

	mDelayLine[mCurrentPos] = output;
	if (mCurrentPos + 1 < mTauSample)
	{
		mCurrentPos++;
	}
	else
	{
		mCurrentPos = 0;
	}
	return output;
}

float MyCombFilter::getFrequencyResponse(float f, int order)
{
	std::complex<float> z(cos(2 * M_PI*f * m1_Fs), sin(2 * M_PI*f * m1_Fs));
	std::complex<float> zn = std::pow(z,mTauSample);

	std::complex<float> h = zn / (zn - mFeedbackGain);

	std::complex<float> hn = h;
	for (int i = 1; i < order; i++) {
		hn = hn*h;
	}

	float abs_hn = std::abs(hn);
	float hn_db = 20 * log10(abs_hn);

	//return 20* std::log10f(std::abs(h));
	return hn_db;

	
}