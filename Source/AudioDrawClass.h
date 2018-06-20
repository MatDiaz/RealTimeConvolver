/*
  ==============================================================================

    AudioDrawClass.h
    Created: 12 Jun 2018 8:57:06pm
    Author:  Mateo Yepes

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AudioDrawClass    : public Component
{
public:
    AudioDrawClass(int updateFrequency);
    ~AudioDrawClass();

    void paint (Graphics&) override;
    void resized() override;
	// Este metodo permite actualizar el buffer que se esta graficando
	// actualment
	void updateBufferToDraw(AudioBuffer<float> bufferToReplace);
	
	// Este metodo se debe llamar desde el componente principal
	void repaintComponent(bool shouldBeRepainting);

	// Este metodo sirve para actualizar el arreglo de datos que contiene
	// la informacion por fotograma
	void updateSumArraySize(int newSize);

private:
	AudioBuffer<float> bufferToDraw;
	AudioBuffer<float> tempDrawBuffer;
	ScopedPointer<float> sumArray;
    bool shouldRepaint, shouldReplace;
    int internalCounter, sizeMultiplier, refreshRate;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioDrawClass)
};
