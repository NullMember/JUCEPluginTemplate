#include <JuceHeader.h>
#include "Plugin.h"

AudioPlugin::AudioPlugin()
    : AudioProcessor (BusesProperties().withInput  ("Input",  AudioChannelSet::stereo())
                                        .withOutput ("Output", AudioChannelSet::stereo()))
{
    addParameter (gain = new AudioParameterFloat ({ "gain", 1 }, "Gain", 0.0f, 1.0f, 0.5f));
}

void AudioPlugin::prepareToPlay (double, int){

}

void AudioPlugin::releaseResources(){

}

void AudioPlugin::processBlock (AudioBuffer<float>& buffer, MidiBuffer&)
{
    buffer.applyGain (*gain);
}

void AudioPlugin::processBlock (AudioBuffer<double>& buffer, MidiBuffer&)
{
    buffer.applyGain ((float) *gain);
}

void AudioPlugin::getStateInformation (MemoryBlock& destData)
{
    MemoryOutputStream (destData, true).writeFloat (*gain);
}

void AudioPlugin::setStateInformation (const void* data, int sizeInBytes)
{
    gain->setValueNotifyingHost (MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat());
}

juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AudioPlugin();
}