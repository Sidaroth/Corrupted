#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include<SFML\Audio.hpp>


class AudioManager 
{

	struct SoundFile
	{
	   SoundFile(const SoundFile& copy) : Name(copy.Name), Vol(copy.Vol), Buffer(copy.Buffer), Sound(copy.Sound)
	   {
		  Sound.setBuffer(Buffer);
	   }

	   std::string Name;
	   float Vol;
	   sf::SoundBuffer Buffer;
	   sf::Sound Sound;
	};

private:
	
	sf::SoundBuffer sb_mBuffer;
	sf::Music m_mMusic;
	sf::Sound s_mSound;
	std::map<std::string,std::string> mp_mBuffer;

public:

	AudioManager();
	bool loadAudio();
	bool playSound(std::string sound_id);
	void loadMap();
	void loadSoundFile(std::string filename, float Volume);
};