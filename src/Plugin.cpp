#include <JuceHeader.h>
#include "Plugin.h"

AudioPlugin::AudioPlugin()
    : AudioProcessor (BusesProperties().withInput  ("Input",  AudioChannelSet::stereo())
                                        .withOutput ("Output", AudioChannelSet::stereo()))
{
    addParameter (gain = new AudioParameterFloat ({ "gain", 1 }, "Gain", 0.0f, 1.0f, 0.5f));
}

void AudioPlugin::prepareToPlay (double sampleRate, int maximumExpectedSamplesPerBlock){

}

void AudioPlugin::releaseResources(){

}

void AudioPlugin::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiBuffer)
{
    buffer.applyGain (*gain);
}

void AudioPlugin::processBlock (AudioBuffer<double>& buffer, MidiBuffer& midiBuffer)
{
    buffer.applyGain ((float) *gain);
}

void AudioPlugin::getStateInformation (MemoryBlock& destData)
{
    MemoryOutputStream* memoryOutputStream = new MemoryOutputStream(destData, true);
    memoryOutputStream.writeFloat(*gain);
    delete memoryOutputStream;
}

void AudioPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    MemoryInputStream* memoryInputStream = new MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false);
    gain->setValueNotifyingHost(memoryInputStream.readFloat());
    delete memoryInputStream;
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPlugin();
}