#include "AudioManager.h"



AudioManager::AudioManager(){
	
	loadMap();
	std::cout << "AudioManager created successfully" << std::endl;

}

bool AudioManager::loadAudio(){ //This is going to be used to load big sounds like music background

	if (!m_mMusic.openFromFile(mp_mBuffer["backing_track"]))
	{
		std::cout << "AudioManager: music can't be loaded" << std::endl;

		return false;
		// Error...
	}
	m_mMusic.setLoop(true);
	m_mMusic.play();
	std::cout << "AudioManager: Music playing and loaded" << std::endl;

	return true;

}

void AudioManager::loadMap(){ //In the future, maybe using an XML??...

	mp_mBuffer["atack_hit"]="../../Resources/sounds/atack_hit.wav";
	mp_mBuffer["atack_miss"]="../../Resources/sounds/atack_miss.wav";
	mp_mBuffer["fireball"]="../../Resources/sounds/fireball.wav";
	mp_mBuffer["fireball_hit"]="../../Resources/sounds/fireball_hit.wav";
	mp_mBuffer["player_gets_hit"]="../../Resources/sounds/get_hit.wav";
	mp_mBuffer["lvl_up"]="../../Resources/sounds/lvl_up.wav";
	mp_mBuffer["move_cursor_options"]="../../Resources/sounds/move_cursor_options.wav";
	mp_mBuffer["select_option"]="../../Resources/sounds/select_option.wav";
	mp_mBuffer["speed_up"]="../../Resources/sounds/speed_up.wav";
	mp_mBuffer["backing_track"]="../../Resources/sounds/bgmusic_temp.ogg";

	std::cout << "AudioManager: Map with sources created" << std::endl;
}

bool AudioManager::playSound(std::string sound_id){

	if(!sb_mBuffer.loadFromFile(mp_mBuffer[sound_id])){
		return false;
	}
	s_mSound.setBuffer(sb_mBuffer);
	s_mSound.play();
	std::cout << "AudioManager: Sound playing..." << std::endl;
}




	

