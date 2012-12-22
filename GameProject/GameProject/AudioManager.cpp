#include "AudioManager.h"



AudioManager::AudioManager()
{

}

AudioManager::~AudioManager()
{

}

bool AudioManager::loadContent()
{
	if (!m_attackHitSound.loadFromFile("../../Resources/sounds/attack_hit.wav"))
	{
		return EXIT_FAILURE;
	}

	if (!m_attackMissSound.loadFromFile("../../Resources/sounds/attack_miss.wav"))
	{
		return EXIT_FAILURE;
	}
	
	if (!m_castFireballSound.loadFromFile("../../Resources/sounds/cast_fireball.wav"))
	{
		return EXIT_FAILURE;
	}
	
	if (!m_fireballHitSound.loadFromFile("../../Resources/sounds/fireball_hit.wav"))
	{
		return EXIT_FAILURE;
	}
	
	if (!m_playerHitSound.loadFromFile("../../Resources/sounds/player_hit.wav"))
	{
		return EXIT_FAILURE;
	}

	if (!m_menuSelectSound.loadFromFile("../../Resources/sounds/menu_select.wav"))
	{
		return EXIT_FAILURE;
	}

	if (!m_statUpgrade.loadFromFile("../../Resources/sounds/stat_upgrade.wav"))
	{
		return EXIT_FAILURE;
	}

	if (!m_heal.loadFromFile("../../Resources/sounds/heal.wav"))
	{
		return EXIT_FAILURE;
	}

	m_musicMap["menuMusic"] = "../../Resources/sounds/FILENAME";
	m_musicMap["gameMusic"] = "../../Resources/sounds/gameMusic.ogg";

	m_soundMap["attack_hit"] = m_attackHitSound;
	m_soundMap["attack_miss"] = m_attackMissSound;
	m_soundMap["cast_fireball"] = m_castFireballSound;
	m_soundMap["fireball_hit"] = m_fireballHitSound;
	m_soundMap["player_hit"] = m_playerHitSound;
	m_soundMap["menu_select"] = m_menuSelectSound;
	m_soundMap["stat_upgrade"] = m_statUpgrade;
	m_soundMap["heal"] = m_heal;

	std::cout << "End of Audio loadContent" << std::endl;
}

bool AudioManager::playMusic(std::string music)
{	
	if (!m_music.openFromFile(m_musicMap[music]))
	{
		return EXIT_FAILURE;
	}

	m_music.setLoop(true);
	m_music.play();
}

void AudioManager::stopOrResumeMusic()
{
	if (m_music.getStatus() == sf::Music::Status::Playing)
	{
		m_music.pause();
	}

	else if (m_music.getStatus() == sf::Music::Status::Paused)
	{
		m_music.play();
	}
}

void AudioManager::playSound(std::string sound)
{
	m_sound.setBuffer(m_soundMap[sound]);
	m_sound.play();
	std::cout << sound << " played" << std::endl;
}




	

