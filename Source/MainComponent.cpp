/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
// Constructor
MainComponent::MainComponent():
// Estas lineas de codigo corresponden a la inicializacion de las diferentes variables
// declaradas en el header, No hay diferencia si esta inicializacion se hace dentro del
// cuerpo del constructor
realTimeDraw(8), 
fileSelected(false), 
shouldBeProcessing(false), 
isBinaural(false), 
shouldRepaint(false)
,audioDrawObject(256, formatManager, audioDrawCache), 
audioDrawCache(1)
{	
	// Definicion de los diferentes objetos utilizados en la interfaz grafica
	// ===========================================================================
    addAndMakeVisible (loadButton = new TextButton ("loadButton"));
    loadButton->setButtonText (CharPointer_UTF8("Cargar IR Mono/Est\xc3\xa9reo"));
    loadButton->addListener (this);

    loadButton->setBounds (127, 130, 150, 24);

    addAndMakeVisible (nameLabelLeft = new Label ("nameLabelLeft",
                                                  TRANS("Nombre:")));
    nameLabelLeft->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    nameLabelLeft->setJustificationType (Justification::centredLeft);
    nameLabelLeft->setEditable (false, false, false);
    nameLabelLeft->setColour (TextEditor::textColourId, Colours::black);
    nameLabelLeft->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    nameLabelLeft->setBounds (24, 200, 344, 24);

    addAndMakeVisible (leftAdress = new Label ("leftAdress",
                                               CharPointer_UTF8 ("Direcci\xc3\xb3n: ")));
    leftAdress->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftAdress->setJustificationType (Justification::centredLeft);
    leftAdress->setEditable (false, false, false);
    leftAdress->setColour (TextEditor::textColourId, Colours::black);
    leftAdress->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    leftAdress->setBounds (24, 168, 344, 24);

    addAndMakeVisible (fsLabelLeft = new Label ("fsLabelLeft",
                                                TRANS("F. Muestreo: ")));
    fsLabelLeft->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    fsLabelLeft->setJustificationType (Justification::centredLeft);
    fsLabelLeft->setEditable (false, false, false);
    fsLabelLeft->setColour (TextEditor::textColourId, Colours::black);
    fsLabelLeft->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    fsLabelLeft->setBounds (24, 264, 344, 24);

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            String()));

    groupComponent->setBounds (24, 59, 360, 56);

    addAndMakeVisible (monoButton = new ToggleButton ("monoButton"));
    monoButton->setButtonText (CharPointer_UTF8("IR Mono/Est\xc3\xa9reo"));
    monoButton->setRadioGroupId (1);
	monoButton->setToggleState(true, dontSendNotification);
    monoButton->addListener (this);

    monoButton->setBounds (32, 78, 152, 24);

    addAndMakeVisible (interleveadStereoButton = new ToggleButton ("interleveadStereoButton"));
    interleveadStereoButton->setButtonText (TRANS("IR Muti-Mono"));
    interleveadStereoButton->setRadioGroupId (1);
    interleveadStereoButton->addListener (this);

    interleveadStereoButton->setBounds (216, 78, 160, 24);

    addAndMakeVisible (channelsLabel = new Label ("channelsLabel",
		CharPointer_UTF8("Configuraci\xc3\xb3n\n")));
    channelsLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    channelsLabel->setJustificationType (Justification::centredLeft);
    channelsLabel->setEditable (false, false, false);
    channelsLabel->setColour (TextEditor::textColourId, Colours::black);
    channelsLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    channelsLabel->setBounds (24, 232, 344, 24);

    addAndMakeVisible (processButton = new TextButton ("processButton"));
    processButton->setButtonText (TRANS("Procesar"));
    processButton->addListener (this);

    processButton->setBounds (32, 488, 344, 24);

	addAndMakeVisible (errorMessage = new AlertWindow("Error", "Error generico", AlertWindow::WarningIcon, nullptr));
	errorMessage->setEscapeKeyCancels(true);
	// ===========================================================================

	// Definimos el objeto para la graficacion del osciloscopio
	addAndMakeVisible(&realTimeDraw);
	//Se definen coordenadas X,Y y dimensiones: Alto y Ancho
	realTimeDraw.setBounds(29.0f, 305.0f, 356.0f, 168.0f);

	// Se asigna un tamaño a la ventana
    setSize (400, 530);

	// Se define una configuracion de canales
    setAudioChannels (2, 2);
    
	// Esto es para el objeto que decodifica los formatos de audio
	// se registran los formatos de audio basicos que JUCE puede manejar
    formatManager.registerBasicFormats();
	// Se inicia un timer para definir el intervalo de tiempo en el que
	// sera llamado el metodo
	// Este valor esta dado en milisegundos
	startTimer(10);
}

// Este es el destructor
MainComponent::~MainComponent()
{	
	// Se "Eliminan" todos los miembros de la clase que hayan sido creados de manera
	// dinamica (ScopedPointer, punteros, etc..)
	loadButton = nullptr;
	nameLabelLeft = nullptr;
	leftAdress = nullptr;
	fsLabelLeft = nullptr;
	groupComponent = nullptr;
	monoButton = nullptr;
	interleveadStereoButton = nullptr;
	channelsLabel = nullptr;
	processButton = nullptr;
	errorMessage = nullptr;

    // Apaga el motor de audio de la aplicacion
    shutdownAudio();
}

//==============================================================================
// Este metodo se llama antes de inicializar el motor de audio
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{	
	// Pasamos el tamaño de Buffer al objeto de osciloscopio
	realTimeDraw.updateSumArraySize(samplesPerBlockExpected);
	// Se asignan las propiedades del motor de reproduccion
	// a las propiedades de la convolucion
	convolutionProperties.sampleRate = sampleRate;
	convolutionProperties.maximumBlockSize = samplesPerBlockExpected;
	convolutionProperties.numChannels = 2;
}

// En este metodo se realiza todo el procesamiento a las señales entrantes
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{	
	// Se comprueba si el boton de procesamiento esta encendido
	if (processButton->getToggleState())
	{	
		// La libreria de JUCE requiere de un objeto especifico para
		// poder realizar su procesmiento de audio, uno se pregunta por que
		// no puede ser el mismo objeto AudioBuffer, y la respuesta es
		// por que ajá.
		dsp::AudioBlock<float> tempAudioBlock(*bufferToFill.buffer);
		// Adicionalmente hay que crear un contexto ( entiendase un contexto como
		// un flujo donde se procesaran los datos, es independiente al thread principal)
		dsp::ProcessContextReplacing<float> ctx(tempAudioBlock);
		// Finalmente pasamos el contexto con el audio block al motor de convolucion
		convolutionEngine.process(ctx);

		// Pasamos el buffer de audio ( ya modificado ) al objeto de osciloscopio en tiempo
		// real
        realTimeDraw.updateBufferToDraw(*bufferToFill.buffer);
	}
	else
	{	// Si el boton de procesamiento esta apagado, entonces no sale ningun sonido
		bufferToFill.clearActiveBufferRegion();
	}
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}
// Este es el metodo que permite actualizar las etiquetas de la interfaz grafica, cada que se ingresa un archivo
void MainComponent::updateLabelText(File originFile, bool rightChannel, double samplingFrequency)
{
	String newName, newAddress, newFs, newConfig;
	// Se declaran variables tipo String para cada uno de los campos, luego
	// Se crean los nuevos textos, a partir de las propiedades del archivo
	newName = "Nombre: " + originFile.getFileName();
	newAddress = CharPointer_UTF8("Direcci\xc3\xb3n: ");
	newAddress = newAddress + originFile.getFullPathName();
	newFs = "F.Muestreo: " + String(samplingFrequency) + " Hz";
	// Se modifican las etiquetas dcon los textos que se crearon
	nameLabelLeft->setText(newName, dontSendNotification);
	leftAdress->setText(newAddress, dontSendNotification);
	fsLabelLeft->setText(newFs, dontSendNotification);
	// Se determina si es monofonico o estereofonico y se modifica la respectiva etiqueta
	if (rightChannel){ channelsLabel->setText(CharPointer_UTF8("Configuraci\xc3\xb3n: Est\xc3\xa9reo"), dontSendNotification);}
	else { channelsLabel->setText(CharPointer_UTF8("Configuraci\xc3\xb3n: Mono"), dontSendNotification);}
}

// Este metodo sirve para actualizar los objetos que realizan el dibujo del archivo cargado
// Actualiza el buffer datos a ser dibujado, la cantidad de muestras y la configuracion de canales 
void MainComponent::updateThumbnail(bool isStereo, int totalLength ,AudioFormatReader* currentReader, AudioBuffer<float> currentAudioBuffer)
{	
	int currentChannels;
	isStereo ? currentChannels = 2 : currentChannels = 1;
	audioDrawObject.reset(currentChannels, currentReader->sampleRate);
	audioDrawObject.addBlock(0, currentAudioBuffer, 0, totalLength);
	shouldRepaint = true;
	repaint();
}
// Este metodo sirve para actualizar el motor de convolucion, ingresando el buffer de datos de la respuesta al impulsso
// la Frec.Muestreo y la configuracion (mono, estereo)
void MainComponent::updateConvolutionEngine(AudioBuffer<float> currentAudioBuffer, AudioFormatReader* currentReader, bool isStereo)
{	
	convolutionEngine.prepare(convolutionProperties);
	convolutionEngine.copyAndLoadImpulseResponseFromBuffer(currentAudioBuffer, currentReader->sampleRate, isStereo, false, false, 0);
}
// Este es el metodo que se llama periodicamente, sirve principalmente para llama al objeto realTimeDraw y refrescar el buffer de datos
void MainComponent::timerCallback()
{	
	// Si el boton esta encendido entonces se grafica las señal, si esta apagado entonces no se grafica nada
	realTimeDraw.repaintComponent(processButton->getToggleState());
}

// Este metodo se llama cada que se presiona el boton, o cada que el procesamiento debe ser
// detenido, lo unico que hace es cambiar el estado del boton y volver a graficar 
void MainComponent::buttonProcessChange()
{
    if (processButton->getToggleState())
    {
        processButton->setToggleState(false, dontSendNotification);
        processButton->setButtonText("Procesar");
		shouldRepaint = true;
    }
    else
    {
        processButton->setToggleState(true, dontSendNotification);
		shouldRepaint = false;
        processButton->setButtonText("Detener");
    }

	repaint();
}

// Este es el metodo callback para todos los botones de la interfaz grafica
void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{	
	// El boton cargar deben principalmente de dos toggle button
	if (buttonThatWasClicked == loadButton)
    {	
		// Se determina si se estan procesando datos, de ser asi, se detiene el proceso
        if (processButton->getToggleState()){buttonProcessChange();}
		// Se declaran los posibles archivos que pueden ser utilizados
        File outputFile, outputFileL, outputFileR;
		// Se declara un audioBuffer para contener estos archivos
        AudioBuffer<float> localAudioBuffer;
        
		// Si el primer Toggle Button esta encendido ( o sea el archivo puede ser mono o estereo )
		if (monoButton->getToggleState())
		{	
			// Usamos el metodo para abrir archivos
			outputFile = loadFiles("Ingrese Archivo Mono o Estereo");
			// Si se seleccional algun archivo
			if (fileSelected)
			{	
				// Reiniciamos el motor de convolucion
				convolutionEngine.reset();
				// Este objeto es el que permite leer como tal el archivo de audio
				ScopedPointer<AudioFormatReader> audioReadOperator;
				audioReadOperator = formatManager.createReaderFor(outputFile);

				// Guardamos la cantidad de muestras del archivo en una variable, pues
				// va a ser utilizada varias veces mas adelante
				int audioLength = (int)audioReadOperator->lengthInSamples;
				// Se le asigna el tamaño al buffer para que pueda almacenar el archivo de audio cargado
				localAudioBuffer.setSize(audioReadOperator->numChannels, audioLength);
				// Se determina si es mono o estereo
				(audioReadOperator->numChannels == 2) ? isBinaural = true : isBinaural = false;
				// Finalmente leemos y guardamos el archivo de audio en el objeto AudioBuffer
				audioReadOperator->read(&localAudioBuffer, 0, audioLength, 0, true, isBinaural);

				// En este momento ya estan los datos del archivo de audio en memoria y 
				// Gracias a que anteriormente se habian creado los metodos para actualizar las etiquetas
				// graficas y motor de convolucion. Lo unico que resta por hacer es llamar a estos metodos
				// y colocar los respectivos argumentos

				updateLabelText(outputFile, isBinaural, audioReadOperator->sampleRate);
				updateThumbnail(isBinaural, audioLength, audioReadOperator, localAudioBuffer);
				updateConvolutionEngine(localAudioBuffer, audioReadOperator, isBinaural);
				
				// Se elimina el lector de audio
                audioReadOperator = nullptr;
			} // Si no se carga un archivo de audio, se muestra este mensaje de error
			else{ errorMessage->showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Ningun Archivo Seleccionado", "Ok", nullptr); }
		}
			// Si cuando se presiona el boton cargar, el toggle button esta en formato multimono
			// Se hace lo siguiente
		else if (interleveadStereoButton->getToggleState())
		{	
			// Se seleccionan los archivos L y R
			outputFileL = loadFiles("Ingrese Archivo L");
			if (fileSelected) { outputFileR = loadFiles("Ingrese Archivo R"); }
			else { errorMessage->showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Ningun Archivo Seleccionado", "Ok", nullptr); }

			// Si se cargan exitosamente ambos archivos
			if (fileSelected)
			{	
				// Se reinicia el motor de convolucion
				convolutionEngine.reset();
				// Como tenemos dos archivos creamos dos lectores de audio (uno para el canal L y otro para el canal R)
				ScopedPointer<AudioFormatReader> audioReadOperatorLeft, audioReadOperatorRight;
				audioReadOperatorLeft = formatManager.createReaderFor(outputFileL);
				audioReadOperatorRight = formatManager.createReaderFor(outputFileR);
                
				// Se obtiene la longitud del audio y se guarda en una variable
                int audioLength = (int)audioReadOperatorLeft->lengthInSamples;
                // Para no tener que crear una cantidad de variables dobles
				// Se crea un array de objetos, en este caso un array de lectores de audio
                OwnedArray<AudioFormatReader> audioArrayHolder;
                // Agregamos los dos lectores a este array 
                audioArrayHolder.add(audioReadOperatorRight);
                audioArrayHolder.add(audioReadOperatorLeft);
                // Se le da el tamaño al buffer que guardara los datos del audio
                localAudioBuffer.setSize(2, audioLength);
                
				// Se crea un ciclo para leer los datos de los archivos de audio
				// y guardarlos en el buffer que creamos 
                for (int i = 0; i < audioArrayHolder.size(); i++)
                {
                    AudioBuffer<float> tempAudioBuffer;
                    tempAudioBuffer.setSize(1, audioLength);
                    audioArrayHolder[i]->read(&tempAudioBuffer, 0, audioLength, 0, true, false);
                    localAudioBuffer.copyFrom(i, 0, tempAudioBuffer, 0, 0, audioLength);
                }

				// En este momento ya estan los datos del archivo de audio en memoria y 
				// Gracias a que anteriormente se habian creado los metodos para actualizar las etiquetas
				// graficas y motor de convolucion. Lo unico que resta por hacer es llamar a estos metodos
				// y colocar los respectivos argumentos
				updateConvolutionEngine(localAudioBuffer, audioArrayHolder[0], isBinaural);
				updateThumbnail(true, audioLength, audioArrayHolder[0], localAudioBuffer);
				updateLabelText(outputFileL, true, audioArrayHolder[0]->sampleRate);

                // Borramos los datos del array de objetos que habiamos creado previamente
                audioArrayHolder.clearQuick(false);
			}// Si no se carga correctamente se saca un ensaje de error
			else{ errorMessage->showMessageBoxAsync(AlertWindow::WarningIcon, "Error", "Ningun Archivo Seleccionado", "Ok", nullptr); }
		}
    }
    else if (buttonThatWasClicked == monoButton)
    {	
		// Si se selecciona el toggle button para (Mono/Estereo) se debe cambiar el texto del boton 
		loadButton->setButtonText(CharPointer_UTF8("Cargar IR Mono/Est\xc3\xa9reo"));
    }
    else if (buttonThatWasClicked == interleveadStereoButton)
    {
		// Si se selecciona el toggle button para (Multi mono) se debe cambiar el texto del boton 
		loadButton->setButtonText("Cargar IR Multi-Mono");
    }
	else if (buttonThatWasClicked == processButton)
	{	
		// Si se presiona el boton de procesamiento se debe cambar el estado actual 
        buttonProcessChange();
	}
}

void MainComponent::userTriedToCloseWindow()
{	
	// Si se selecciona el toggle button para (Mono/Estereo) se debe cambiar el texto del boton 
	if (processButton->getToggleState()) { buttonProcessChange(); }
}

// Este metodo es el que permite cargar archivos
File MainComponent::loadFiles(const String stringToShow)
{	
	// Se crea un objeto de tipo de FileChooser, que es el que permite abrir la ventana de seleccion de archivo
	FileChooser newFileChooser(stringToShow, File::getSpecialLocation(File::userDesktopDirectory), "*.wav");
    
    File newFile;
	// Si el usuario selecciona un archivo entonces se pasa el archivo a la variable que lo esta recibiendo 
	if (newFileChooser.browseForFileToOpen())
    {
		newFile = newFileChooser.getResult();
        fileSelected = true;
    }
    else
    {
        fileSelected = false;
    }
    
    return newFile;
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff242424));

    {
        int x = 28, y = 16, width = 350, height = 32;
        String text (TRANS("Real Time Convolver"));
        Colour fillColour = Colours::white;
        g.setColour (fillColour);
        g.setFont (Font (27.40f, Font::plain).withTypefaceStyle ("Bold"));
        g.drawText (text, x, y, width, height,
                    Justification::centred, true);
    }

    {
        float x = 29.0f, y = 305.0f, width = 356.0f, height = 168.0f;
        Colour fillColour = Colour (0xff3c3c3c);
        Colour strokeColour = Colours::white;
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 10.000f);
        g.setColour (strokeColour);
        g.drawRoundedRectangle (x, y, width, height, 10.000f, 0.500f);

		// Este rectangulo es donde estara dibujado el archivo que se cargue
		Rectangle<int> thumbnailBounds(x*1.05, y*1.025, width*0.995, height*0.9);

		// Si se debe volver a graficar el archivo
		if (shouldRepaint)
		{
			g.setColour(Colours::transparentWhite);
			g.fillRect(thumbnailBounds);
            g.setColour(Colours::white);
			// Se pasan los argumentos respectivos al objeto
			audioDrawObject.drawChannels(g, thumbnailBounds, 0, audioDrawObject.getTotalLength(), 3.0f);
		}
    }
}

void MainComponent::resized()
{
   
}
