#pragma once

#include "GameState.h"
#include "StateHandler.h"
#include "SFML/Network.hpp"

#include "json/json_spirit.h"
#include "json/json_spirit_reader_template.h"
#include "json/json_spirit_writer_template.h"

#include <fstream>
#include <iostream>

#ifndef JSON_SPIRIT_MVALUE_ENABLED
#error Please define JSON_SPIRIT_MVALUE_ENABLED for the mValue type to be enabled 
#endif

using namespace json_spirit;

class Highscore : public GameState
{
private:

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::Text m_usernameText;
	sf::Font m_impactFont;

	std::string m_sJson;
	std::string m_sUsername;

	struct User
	{
		std::string name;
		std::string score;
	};

	std::vector< User > leaderboard;
public:
	Highscore();
	~Highscore();

	void loadContent(sf::RenderWindow* window);
	void unloadContent();
	void processEvents(sf::Event event);
	void update();
	void draw();

	std::string httpGet(std::string host, std::string path);

	void drawLeaderboard();

	void decodeJson();
	
	User read_user( const mObject& obj );
	const mValue& find_value( const mObject& obj, const std::string& name  );
	std::vector< Highscore::User > read_entries( const char* file_name );
	void write_user( mArray& a, const Highscore::User& user );

	friend bool operator== ( const User& a1, const User& a2 )
	{
		return	( a1.name == a2.name ) &&
				( a1.name == a2.name );
	}
};