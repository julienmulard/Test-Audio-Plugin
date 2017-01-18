#include "MyFilter.h"

MyFilter::MyFilter(float cutoff, float sampleRate) 
{
	mCutoffFrequency = cutoff;
	mSampleRate = sampleRate;
}

MyFilter::~MyFilter()
{
}

void MyFilter::setCutoff(float cutoff) {
	mCutoffFrequency = cutoff;
}

void MyFilter::setSampleRate(float sampleRate) {
	mSampleRate = sampleRate;
}