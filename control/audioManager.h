#pragma
#include <SDL_mixer.h>

#define MAX_SOUNDS 10

struct AudioEvent {
	// flag indicating which index in sounds array to play.
	int index;
};

class AudioManager {
	// Flag to control music; -1 indicates no sound to be played. 0 or greater indicates a which sounds in the sounds array needs to be played
	int playing;
	// Collection of sounds this button AI can play. Control using playSound.
	Mix_Chunk* sounds[MAX_SOUNDS];

public:
	AudioManager();
	~AudioManager();

	void update();
	void loadSound(const char* sound, int index);
	void playSound(int index);

	int isPlaying() { return playing; };
	Mix_Chunk* getSound(int index) { return sounds[index]; };

	void setPlaying(int p) { playing = p; };
};