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
	// Se inicializan las variables declaradas en el header
	shouldRepaint(false), 
	internalCounter(0), 
	sizeMultiplier(1), 
	refreshRate(updateFrequency), 
	shouldReplace(true)
 {
	// Se inicializan el resto de objetos
     bufferToDraw.setSize (1, getWidth());
	 tempDrawBuffer.setSize (1, getWidth());
     bufferToDraw.clear();
	 tempDrawBuffer.clear();

	 sumArray = new float[getWidth()];
	 memset(sumArray, 0, sizeof(float) * getWidth());
	
 }

  AudioDrawClass::~AudioDrawClass()
{	
	  // Se elimina el arreglo creado
	  sumArray = nullptr;
}

  // Esta es la clase que permite realizar la grafica tambien
void AudioDrawClass::paint (Graphics& g)
{
	if (shouldRepaint)
	{	
		// La manera para graficar, es hacer una linea que vaya recorriendo punto
		// por punto los valores del buffer de datos, para esto se debe crear
		// un objeto de dibujo
		Path drawPath;

		// Se le asigna un punto de partida
		drawPath.startNewSubPath(0, round(getHeight()/2));
        // Obtenemos el puntero de lectura para el buffer de datos de entrada
        const float* channelN = tempDrawBuffer.getReadPointer(0);
        
		// Luego recorremos punto por punto el buffer datos que se va a graficaar
		for (int i = 0; i < getWidth(); i++)
		{	
			// Se debe tener en cuenta que se debe extraer cada elemento del vector, ubicarlo en medio de la grafica
			// ademas se debe de multiplicar por la mitad de la altura de la grafica
			// adicionalmente se le debe de sumar un factor de suavizado
			int pathPoint = ((channelN[i * sizeMultiplier] + (sumArray[i * sizeMultiplier] * internalCounter)) * getHeight()/2) + (getHeight()/2);
            drawPath.lineTo(i, pathPoint);
		}
        // Se le asigna un color
        g.setColour (Colour (0x97ffffff));
		// Se genera la linea
        g.strokePath (drawPath, PathStrokeType(1.0f));

		// Se aumenta la posicion en el factor de suavizado
		internalCounter++;

		if (internalCounter >= refreshRate)
        {
            shouldReplace = true;
            internalCounter = 1;
        }
	}
}

void AudioDrawClass::resized()
{

}

void AudioDrawClass::updateBufferToDraw(AudioBuffer<float> bufferToReplace)
{
	if (shouldRepaint && shouldReplace)
    {	
		// Si el tamaño del buffer es mayor/menor al area de dibujo se debe hacer
		// un ajuste al avance del vector, aca se calcula ese ajuste
		sizeMultiplier = floor(getWidth() / bufferToReplace.getNumSamples());
		if (sizeMultiplier <= 0) { sizeMultiplier = 1; }

		// Para el factor de suavizado necesitamos dos buffer, un buffer de partida
		// un buffer de llegada
		// El buffer de partida sera el buffer que habia anteriormente
		// El buffer de llegada sera el nuevo buffer entrante
		tempDrawBuffer = bufferToDraw;
		bufferToDraw = bufferToReplace;
		
		// Obtenemos los punteros de lectura de cada buffer 
		const float*  destinationValue  = bufferToDraw.getReadPointer(0);
		const float*  startValue = tempDrawBuffer.getReadPointer(0);

		// Recorremos punto por punto los buffer, se encuentra la diferencia y se divide por la tasa de refresco
		// esta, es asignada previamente por el usuario
		for (int i = 0; i < tempDrawBuffer.getNumSamples(); i++)
			sumArray[i] = (destinationValue[i] - startValue[i]) / ((float) refreshRate);
        
        shouldReplace = false;
    }
}

void AudioDrawClass::repaintComponent(bool shouldBeRepainting)
{	
	shouldRepaint = shouldBeRepainting;
	// Este metodo se llama cuando ya no se quiere dibujar la grafica
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

// Este es el metodo para cambiar el tamaño del array que contiene los datos del factor de suavizado
void AudioDrawClass::updateSumArraySize(int newSize)
{
	if (sumArray != nullptr){ sumArray = nullptr; }
	sumArray = new float[newSize];
	memset(sumArray, 0, sizeof(float) * newSize);
}
