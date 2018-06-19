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
	shouldRepaint(false), internalCounter(0), sizeMultiplier(1), refreshRate(updateFrequency)
 {
     bufferToDraw.setSize (1, getWidth());
	 tempDrawBuffer.setSize (1, getWidth());
     bufferToDraw.clear();
	 tempDrawBuffer.clear();

	 sumArray = new float[getWidth()];
	 memset(sumArray, 0, sizeof(float) * getWidth());
	
 }

  AudioDrawClass::~AudioDrawClass()
{
	  sumArray = nullptr;
}

void AudioDrawClass::paint (Graphics& g)
{
	if (shouldRepaint)
	{
		Path drawPath;

		drawPath.startNewSubPath(0, round(getHeight()/2));
        
        const float* channelN = bufferToDraw.getReadPointer(0);
        
		for (int i = 0; i < getWidth(); i++)
		{	
			int pathPoint = channelN[i * sizeMultiplier];
			pathPoint = ((pathPoint + (getHeight() / 2)) * getHeight());
            drawPath.lineTo(i, pathPoint);
		}

		internalCounter++;

		if (internalCounter >= refreshRate) { internalCounter = 1; }
        
        g.setColour (Colour (0x97ffffff));
        g.strokePath (drawPath, PathStrokeType(1.0f));
	}
}

void AudioDrawClass::resized()
{

}

void AudioDrawClass::updateBufferToDraw(AudioBuffer<float> bufferToReplace)
{
	if (shouldRepaint)
    {
		tempDrawBuffer = bufferToDraw;
		bufferToDraw = bufferToReplace;
		
		sizeMultiplier = floor(getWidth() / bufferToReplace.getNumSamples());
		if (sizeMultiplier <= 0) { sizeMultiplier = 1; }
		
		const float*  destinationValue  = bufferToDraw.getReadPointer(0);
		const float*  startValue = tempDrawBuffer.getReadPointer(0);

		for (int i = 0; i < tempDrawBuffer.getNumSamples(); i++)
		{
			sumArray[i] = (destinationValue[i] - startValue[i]) / ((float)refreshRate);
		}
    }
}

void AudioDrawClass::repaintComponent(bool shouldBeRepainting)
{	
	shouldRepaint = shouldBeRepainting;
	
	if (shouldBeRepainting)
	{	
		setVisible(true);
		repaint();
	}
	else
	{
		setVisible(false);
	}
}

void AudioDrawClass::updateSumArraySize(int newSize)
{
	if (sumArray != nullptr){ sumArray = nullptr; }
	sumArray = new float[newSize];
	memset(sumArray, 0, sizeof(float) * newSize);
}
