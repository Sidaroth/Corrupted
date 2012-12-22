#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include<SFML\Audio.hpp>


class AudioManager 
{

private:
	
	sf::Sound m_sound;
	sf::Music m_music;

	std::map<std::string, sf::SoundBuffer> m_soundMap;
	std::map<std::string, std::string> m_musicMap;


	sf::SoundBuffer m_attackHitSound;
	sf::SoundBuffer m_attackMissSound;
	sf::SoundBuffer m_castFireballSound;
	sf::SoundBuffer m_fireballHitSound;
	sf::SoundBuffer m_playerHitSound;
	sf::SoundBuffer m_menuSelectSound;
	sf::SoundBuffer m_statUpgrade;
	sf::SoundBuffer m_heal;


public:

	AudioManager();
	~AudioManager();

	bool loadContent();

	bool playMusic(std::string music);
	void stopOrResumeMusic();

	void playSound(std::string sound);
};