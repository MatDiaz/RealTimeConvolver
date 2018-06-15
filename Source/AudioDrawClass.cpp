/*
  ==============================================================================

    AudioDrawClass.cpp
    Created: 12 Jun 2018 8:57:06pm
    Author:  Mateo Yepes

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "AudioDrawClass.h"

//==============================================================================
AudioDrawClass::AudioDrawClass(int updateFrequency):
	shouldRepaint(false)
 {

 }

  AudioDrawClass::~AudioDrawClass()
{

}

void AudioDrawClass::paint (Graphics& g)
{
	if (shouldRepaint)
	{
		Path drawPath;

		drawPath.startNewSubPath(0, round(getHeight()/2));

		for (int i = 0; i < getWidth(); i++)
		{

		}
	}
}

void AudioDrawClass::resized()
{

}

void AudioDrawClass::updateBufferToDraw(AudioBuffer<float> bufferToReplace)
{
	bufferToDraw = bufferToReplace;
	shouldRepaint = true;
}

void AudioDrawClass::repaintComponent(bool shouldReplaceBuffer)
{
}
