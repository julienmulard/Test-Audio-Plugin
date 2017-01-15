#include "SpectrumDisplay.h"

SpectrumDisplay::SpectrumDisplay(float min_freq, float max_freq, float min_amp, float max_amp)
{
	mMin_freq = min_freq;
	mMax_freq = max_freq;
	mMin_amp = min_amp;
	mMax_amp = max_amp;

	frequencyResponseDisplay = new FrequencyResponseDisplay(mMin_freq, mMax_freq, mMin_amp, mMax_amp);

	addAndMakeVisible(frequencyResponseDisplay);
}

SpectrumDisplay::~SpectrumDisplay()
{
	delete frequencyResponseDisplay;
}

void SpectrumDisplay::paint(Graphics &g)
{



	int w = getWidth();
	int h = getHeight();
	
	g.setColour(Colours::black);
	g.fillRect(0.0f, 0.0f, float(getWidth()), float(getHeight()));


	float offset_x_l = 0;
	float offset_x_r = 0;
	float offset_y_u = 0;
	float offset_y_d = 0;

	float freq_offset = log10f(mMin_freq); //offset des valeurs de fréquences (on est en log, on ne peux pas partir de 0)
	float freq_gain = (w - offset_x_r) / (log10f(mMax_freq) - freq_offset);

	float amp_offset = mMax_amp / (mMax_amp - mMin_amp)*h; //offset des amplitudes, i.e. la ou sera le 0dB en fonction de la taille du component
	float amp_gain = amp_offset / mMax_amp; //facteur d'échelle 

	Array<float> freqs = { 20,30,40,50,60,70,80,90,100,200,300,400,500,600,700,800,900,1000,2000,3000,4000,5000,6000,7000,8000,9000,10000,20000 };
	
	g.setColour(Colours::darkgrey);

	for (int i = 0; i < freqs.size(); i++)
	{
		float posx = (log10(freqs[i]) - freq_offset) * freq_gain;
		g.drawLine(posx, 0, posx, h);
	}

	
	for (int i = int(mMin_amp); i<int(mMax_amp) + 1; i = i + 2) {
		float posy = amp_offset - i*amp_gain;
		g.drawLine(0, posy, w, posy);
	}

	


}


void SpectrumDisplay::resized()
{
	frequencyResponseDisplay->setBounds(0, 0, getWidth(), getHeight());
}

void SpectrumDisplay::setFilterResponsePath(Array<float> frequencies, Array<float> amplitudes, float cutoff)
{
	frequencyResponseDisplay->setFilterResponsePath(frequencies, amplitudes,cutoff);
	
}