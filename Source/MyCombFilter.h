#pragma once

#include "MyFilter.h"
#include<cmath>
#include<complex>

# define M_PI           3.14159265358979323846

class MyCombFilter:public MyFilter
{
public:
	MyCombFilter(float cutoff, float feedbackGain, float sampleRate);
	~MyCombFilter();

	void setSampleRate(float sampleRate) override;
	void setCutoff(float cutoff) override;
	
	void setFeedbakcGain(float feedbackGain);

	void setFilter(float cutoff, float feedbackGain) override;

	float getFrequencyResponse(float f, int order = 1) override;

	float filter(float input) override;

	

private:
	float m1_Fs;

	float mFeedbackGain;

	static const int mMaxDelay = 2205;

	float mDelayLine[mMaxDelay];

	int mTauSample;

	int mCurrentPos;
};
