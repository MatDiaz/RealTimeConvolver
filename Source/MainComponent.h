/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
// AudioDrawClass es una clase creada por mi, para manejar la graficación del osciloscopio
// de manera independiente al componente principal
#include "AudioDrawClass.h"

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/
class MainComponent   : public AudioAppComponent,
                        public Button::Listener,
						private Timer
{
public:
    //==============================================================================
    MainComponent();
    ~MainComponent();

    //==============================================================================
    void prepareToPlay (int samplesPerBlockExpected, double sampleRate) override;
    void getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;

    //==============================================================================
    void paint (Graphics& g) override;
    void resized() override;
    
	// Este metodo proviene de la clase heredada "public Button::Listener" 
	// servira como callback para cuando el usuario presione cualquiera de los botones
	// dentro de la interfaz grafica
    void buttonClicked (Button* buttonThatWasClicked) override;

	// Este metodo proviene de la clase heredada "public AudioAppComponent" 
	// Se llamara cuando el usuario cierre la aplicacion y sirve para asegurarnos de que se cierren todos los
	// procesos
	void userTriedToCloseWindow() override;

	// Este metodo sirve para juntar todos los pasos necesarios para cargar un archivo, devuelve el archivo
	File loadFiles (const String stringToShow);
    
	// Este metodo sirve para actualizar los campos de texto creados en la interfaz gráfica
	void updateLabelText (File originFile, bool rightChannel, double samplingFrequency);

	// Este metodo sirve para actualizar la imagen del archivo cargado en la interfaz grafica
	void updateThumbnail(bool isStereo, int totalLength, AudioFormatReader* currentReader, AudioBuffer<float> currentAudioBuffer);

	// Este metodo sirve para actualizar el objeto de convolucion, se llamara cada que se cargue un archivo nuevo 
	void updateConvolutionEngine(AudioBuffer<float> currentAudioBuffer, AudioFormatReader* currentReader, bool isStereo);
	
	// Este metodo proviene de la clase heredada "private Timer"
	// Este metodo se llamara periodicamente para ejecutar ciertas acciones
	// En este caso, para actualizar el osciloscopio 
	void timerCallback() override;

	// Este metodo se llama cada que el procesamiento de cambiar/reanudar
	void buttonProcessChange();

private:
    //==============================================================================
    // Your private member variables go here...

	// Estos son objetos creados para la interfaz grafica
	// Botones, texto, etc...
	// ==================================================
    ScopedPointer<TextButton> loadButton;
    ScopedPointer<Label> nameLabelLeft;
    ScopedPointer<Label> leftAdress;
    ScopedPointer<Label> fsLabelLeft;
    ScopedPointer<GroupComponent> groupComponent;
    ScopedPointer<ToggleButton> monoButton;
    ScopedPointer<ToggleButton> interleveadStereoButton;
    ScopedPointer<Label> channelsLabel;
    ScopedPointer<TextButton> processButton;
	// ==================================================
	// Esta es la ventana de alerta que saltara cuando haya algun error
	ScopedPointer<AlertWindow> errorMessage;

	// Esta es la clase para el dibujo en tiempo real del osciloscopio
	// Esta creada de manera estatica, pero no hay ninguna diferencia si se crea
	// de manera dinamica (ScopedPointer, Punteros...)
	AudioDrawClass realTimeDraw;
    
	// Este es un objeto de JUCE, que se utiliza para decodificar los diferentes
	// formatos de audio que se puedan cargar desde un archivo
	// (.mp3, .wav, .aiff, etc)
    AudioFormatManager formatManager;
	
	// Una lista de diferentes booleanos necesarios para el funcionamiento
    bool fileSelected, shouldBeProcessing, isBinaural, shouldRepaint;

	// Estos son dos objetos de JUCE y se utilizan para dibujar el archivo cargado
	AudioThumbnail audioDrawObject;
	AudioThumbnailCache audioDrawCache;

	// Estos son dos objetos de JUCE, de la libreria de DSP, y son los utilizados
	// para realizar la convolucion, convolutionProperties son las propiedades de la convolucion
	// Frec.Muestreo, Canales, Tam.Buffer, Etc...
	// convolutionEngine es el motor de convolucion como tal ( el que realizar el proceso )
	dsp::Convolution convolutionEngine;
	dsp::ProcessSpec convolutionProperties;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainComponent)
};
