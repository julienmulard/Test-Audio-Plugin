#pragma once

class MyFilter
{
public:
	MyFilter(float cutoff = 1000, float sampleRate = 44100);
	~MyFilter();

	virtual void setSampleRate(float sampleRate);
	virtual void setCutoff(float cutoff);

	virtual void setFilter(float cutoff, float param) = 0;

	virtual float getFrequencyResponse(float f, int order = 1) = 0;

	virtual float filter(float input) = 0;

	
protected:
	float mSampleRate;
	float mCutoffFrequency;

};

