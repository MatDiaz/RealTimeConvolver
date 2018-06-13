/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
MainComponent::MainComponent():
fileSelected(false), shouldBeProcessing(false), isBinaural(false), shouldRepaint(false)
,audioDrawCache(5), audioDrawObject(512, formatManager, audioDrawCache)
{
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

    setSize (400, 530);

    setAudioChannels (2, 2);
    
    formatManager.registerBasicFormats();
}

MainComponent::~MainComponent()
{   
	loadButton = nullptr;
	nameLabelLeft = nullptr;
	leftAdress = nullptr;
	fsLabelLeft = nullptr;
	groupComponent = nullptr;
	monoButton = nullptr;
	interleveadStereoButton = nullptr;
	channelsLabel = nullptr;
	processButton = nullptr;

    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
	convolutionProperties.sampleRate = sampleRate;
	convolutionProperties.maximumBlockSize = samplesPerBlockExpected;
	convolutionProperties.numChannels = 2;
}

void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
	if (processButton->getToggleState())
	{
		dsp::AudioBlock<float> tempAudioBlock(*bufferToFill.buffer);
		dsp::ProcessContextReplacing<float> ctx(tempAudioBlock);
		convolutionEngine.process(ctx);
	}
	else
	{
		bufferToFill.clearActiveBufferRegion();
	}
}

void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()
}

void MainComponent::updateLabelText(File originFile, bool rightChannel, double samplingFrequency)
{
	String newName, newAddress, newFs, newConfig;
	newName = "Nombre: " + originFile.getFileName();
	newAddress = CharPointer_UTF8("Direcci\xc3\xb3n: ");
	newAddress = newAddress + originFile.getFullPathName();
	newFs = "F.Muestreo: " + String(samplingFrequency) + " Hz";

	nameLabelLeft->setText(newName, dontSendNotification);
	leftAdress->setText(newAddress, dontSendNotification);
	fsLabelLeft->setText(newFs, dontSendNotification);
	
	if (rightChannel){ channelsLabel->setText(CharPointer_UTF8("Configuraci\xc3\xb3n: Est\xc3\xa9reo"), dontSendNotification);}
	else { channelsLabel->setText(CharPointer_UTF8("Configuraci\xc3\xb3n: Mono"), dontSendNotification);}
}

void MainComponent::buttonProcessChange()
{
    if (processButton->getToggleState())
    {
        processButton->setToggleState(false, dontSendNotification);
        processButton->setButtonText("Procesar");
    }
    else
    {
        processButton->setToggleState(true, dontSendNotification);
        processButton->setButtonText("Detener");
    }
}

void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == loadButton)
    {
        if (processButton->getToggleState()){buttonProcessChange();}
        
		convolutionEngine.reset();

        File outputFile, outputFileL, outputFileR;
        
		if (monoButton->getToggleState())
		{
			outputFile = loadFiles("Ingrese Archivo Mono");
		}
		else if (interleveadStereoButton->getToggleState())
		{
			outputFileL = loadFiles("Ingrese Archivo L");
			if (fileSelected) { outputFileR = loadFiles("Ingrese Archivo R"); }
			else {}
		}

		// Si el archivo seleccionado se carga de manera correcta
	    // El booleano fileSelected se modifica desde el método loadFiles
        if(fileSelected)
        {
			// Creamos una clase que nos permita leer el archivo de audio que acabamos de crear
			// Esta clase depende explicitamente del objeto formatManager, creado desde el header
			// El objeto formatManager es quien permite decodificar los diferentes formatos de audio (.wav, .mp3, .aiff...)
            ScopedPointer<AudioFormatReader> audioReadOperator;
            audioReadOperator = formatManager.createReaderFor(outputFile);
			// Se crea un lector para el archivo de entrada
            
			audioBufferZero.setSize(audioReadOperator->numChannels, (int)audioReadOperator->lengthInSamples);

            // Se leen los datos como tal y se guardan en el buffer
            audioReadOperator->read(&audioBufferZero, 0, (int)audioReadOperator->lengthInSamples, 0, true, true);

			(audioReadOperator->numChannels == 2) ? isBinaural = true: isBinaural = false;

			convolutionEngine.prepare(convolutionProperties);

			convolutionEngine.copyAndLoadImpulseResponseFromBuffer(audioBufferZero, audioReadOperator->sampleRate, true, false, false, 0);

			updateLabelText(outputFile, isBinaural, audioReadOperator->sampleRate);

			audioDrawObject.setSource(new FileInputSource(outputFile));

			shouldRepaint = true;
			
			repaint();
        }
        else
        {
            
        }
    }
    else if (buttonThatWasClicked == monoButton)
    {
		loadButton->setButtonText(CharPointer_UTF8("Cargar IR Mono/Est\xc3\xa9reo"));
    }
    else if (buttonThatWasClicked == interleveadStereoButton)
    {
		loadButton->setButtonText("Cargar IR Multi-Mono");
    }
	else if (buttonThatWasClicked == processButton)
	{
        buttonProcessChange();
	}
}

File MainComponent::loadFiles(const String stringToShow)
{
	FileChooser newFileChooser(stringToShow, File::getSpecialLocation(File::userDesktopDirectory), "*.wav");
    
    File newFile;

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

		Rectangle<int> thumbnailBounds(x, y, width*0.9, height*0.9);

		if (shouldRepaint)
		{	
			g.setColour(Colours::transparentWhite);
			g.fillRect(thumbnailBounds);
			g.setColour(Colours::white);
			audioDrawObject.drawChannels(g, thumbnailBounds, 0, audioDrawObject.getTotalLength(), 1.0f);
		}
    }
}

void MainComponent::resized()
{
    // This is called when the MainContentComponent is resized.
    // If you add any child components, this is where you should
    // update their positions.
}
