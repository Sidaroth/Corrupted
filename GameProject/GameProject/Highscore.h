#pragma once

#include "GameState.h"
#include "StateHandler.h"
#include "SFML/Network.hpp"

#include "json/json_spirit.h"
#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"

#include <fstream>
#include <iostream>
#include <iomanip>

#include "TitleScreen.h"

#ifndef JSON_SPIRIT_MVALUE_ENABLED
#error Please define JSON_SPIRIT_MVALUE_ENABLED for the mValue type to be enabled 
#endif

using namespace json_spirit;

class Highscore : public GameState
{
private:
	sf::RenderWindow* m_window;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;

	sf::Texture m_mainMenuTexture;
	sf::Texture m_mainMenuPressTexture;
	sf::Sprite m_mainMenuSprite;

	sf::Texture m_submitTexture;
	sf::Texture m_submitPressTexture;
	sf::Sprite m_submitSprite;

	sf::Texture m_textFieldTexture;
	sf::Sprite m_textFieldSprite;

	sf::Text m_usernameText;
	sf::Text m_leaderboardText;
	sf::Text m_submitErrorText;
	sf::Text m_userScore;

	sf::Font m_font;

	std::string m_sJson;
	std::string m_sUsername;

	bool m_bNothingTyped;
	bool m_bSubmitted;

	int m_iScrollPos;
	int m_iMaxScrollPos;
	int m_iMinScrollPos;

	int m_iScore;

	struct User
	{
		std::string name;
		std::string score;
	};

	std::vector< User > leaderboard;
public:
	Highscore();
	Highscore( short score );
	~Highscore();

	void loadContent();
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();

	std::string httpGet(std::string host, std::string path);

	void reloadLeaderboard();

	void decodeJson();
	
	User read_user( const mObject& obj );
	const mValue& find_value( const mObject& obj, const std::string& name  );
	std::vector< Highscore::User > read_entries( const char* file_name );
	void write_user( mArray& a, const Highscore::User& user );

	bool isalnumch(char ch);
	bool isalnumstr(std::string str);

	friend bool operator== ( const User& a1, const User& a2 )
	{
		return	( a1.name == a2.name ) &&
				( a1.name == a2.name );
	}
};