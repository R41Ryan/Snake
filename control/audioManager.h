#pragma
#include <SDL_mixer.h>
#include <dataStructures.h>

#define MAX_SOUNDS 10

struct AudioEvent {
	// flag indicating which index in sounds array to play.
	int index;
};

class AudioManager {
	LinkedList<AudioEvent> audioQueue;
	// Collection of sounds this button AI can play. Control using playSound.
	Mix_Chunk* sounds[MAX_SOUNDS];

public:
	AudioManager();
	~AudioManager();

	void update();
	void loadSound(const char* sound, int index);
	void playSound(int index);

	Mix_Chunk* getSound(int index) { return sounds[index]; };
	LinkedList<AudioEvent> getAudioQueue() { return audioQueue; };
};