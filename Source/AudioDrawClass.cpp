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
	shouldRepaint(false), internalCounter(0)
 {
     bufferToDraw.setSize(1, getWidth());
     bufferToDraw.clear();
 }

  AudioDrawClass::~AudioDrawClass()
{

}

void AudioDrawClass::paint (Graphics& g)
{
	if (shouldRepaint)
	{
        shouldRepaint = false;
        
		Path drawPath;

		drawPath.startNewSubPath(0, round(getHeight()/2));
        
        const float* channelN = bufferToDraw.getReadPointer(0);
        
		for (int i = 0; i < getWidth(); i++)
		{
            drawPath.lineTo(i, ((channelN[i]) * (getHeight())) + round(getHeight()/2));
		}
        
        g.setColour (Colour (0x97ffffff));
        g.strokePath (drawPath, PathStrokeType(1.0f));
        
        shouldRepaint = true;
	}
}

void AudioDrawClass::resized()
{

}

void AudioDrawClass::updateBufferToDraw(AudioBuffer<float> bufferToReplace)
{
    shouldRepaint = true;
	if (shouldRepaint)
    {
        bufferToDraw = bufferToReplace;
    }
}

void AudioDrawClass::repaintComponent(bool shouldReplaceBuffer)
{
    repaint();
}
