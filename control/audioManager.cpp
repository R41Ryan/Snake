#include "audioManager.h"
#include <iostream>

bool AudioManager::enableMusic = true;
bool AudioManager::enableSound = true;

AudioManager::AudioManager()
{
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		sounds[i] = nullptr;
	}
}

AudioManager::~AudioManager()
{
	for (int i = 0; i < MAX_SOUNDS; i++)
	{
		if (sounds[i] != nullptr)
			Mix_FreeChunk(sounds[i]);
	}
}

void AudioManager::update()
{
	while (audioQueue.getCount() > 0) {
		Mix_PlayChannel(-1, sounds[audioQueue.popHead().index], 0);
	}
}

void AudioManager::loadSound(const char* sound, int index)
{
	if (index < 0 || index >= MAX_SOUNDS)
	{
		std::cout << "Error loading sound: index is out of bounds.\n";
		return;
	}
	if (sounds[index] != nullptr)
		Mix_FreeChunk(sounds[index]);
	sounds[index] = Mix_LoadWAV(sound);
	if (sounds[index] == nullptr)
	{
		std::cout << "Error loading sound: Invalid file path.\n";
		return;
	}
}

void AudioManager::playSound(int index)
{
	if (enableSound) {
		if (index < 0 || index >= MAX_SOUNDS)
		{
			std::cout << "Error playing sound: index is out of bounds.\n";
			return;
		}
		if (sounds[index] == nullptr)
		{
			std::cout << "Error playing sound: sound index is null.\n";
			return;
		}
		if (sounds[index] != nullptr) {
			AudioEvent newEvent{ index };
			audioQueue.addItemToEnd(newEvent);
		}
	}
}