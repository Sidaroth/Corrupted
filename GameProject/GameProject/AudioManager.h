#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include<SFML\Audio.hpp>


class AudioManager 
{
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

};