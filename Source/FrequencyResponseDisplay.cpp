#include "FrequencyResponseDisplay.h"

FrequencyResponseDisplay::FrequencyResponseDisplay(float min_freq, float max_freq, float min_amp, float max_amp)
{
	mMin_freq = min_freq;
	mMax_freq = max_freq;
	mMin_amp = min_amp;
	mMax_amp = max_amp;
}

FrequencyResponseDisplay::~FrequencyResponseDisplay()
{
}

void FrequencyResponseDisplay::paint(Graphics &g)
{	
	//g.setColour(Colours::black);
	//g.fillRoundedRectangle(0.0f,0.0f,float(getWidth()), float(getHeight()), 5);
	
	g.setColour(Colours::green);
	if (!filterResponse.isEmpty()) {
		g.strokePath(filterResponse, PathStrokeType(2.0f));
		filterResponse.clear();
		g.setColour(Colours::red);
		g.drawLine(mXCutoff, 0, mXCutoff, getHeight());
	}
	
		
	
}

void FrequencyResponseDisplay::setFilterResponsePath(Array<float> frequencies, Array<float> amplitudes, float cutoff)
{
	
	if (frequencies.size() == amplitudes.size())
	{
		int w = getWidth();
		int h = getHeight();

		//offsets en pixel qui détermine la zone dans laquelle on trace la courbe
		float offset_x_l = 0;
		float offset_x_r = 0;
		float offset_y_u = 0;
		float offset_y_d = 0;

		float freq_offset = log10f(mMin_freq); //offset des valeurs de fréquences (on est en log, on ne peux pas partir de 0)
		float freq_gain = (w-offset_x_r) / (log10f(mMax_freq) - freq_offset);


		float amp_offset = mMax_amp/(mMax_amp-mMin_amp)*h; //offset des amplitudes, i.e. la ou sera le 0dB en fonction de la taille du component
		float amp_gain = amp_offset / mMax_amp; //facteur d'échelle 

		

		filterResponse.startNewSubPath(offset_x_l, amp_offset - amplitudes[0]*amp_gain);
		for (int i = 1; i < amplitudes.size(); i++) {

			float freq = frequencies[i];
			float log_freq = log10f(freq);
			float x = (log_freq - freq_offset) * freq_gain;

			float response = amplitudes[i] * amp_gain;
			float y = amp_offset - response;
			filterResponse.lineTo(x, y);
		}

		 mXCutoff = (log10f(cutoff) - freq_offset) * freq_gain;

		//filterResponse = filterResponsePath;
		repaint();
	}
	
}