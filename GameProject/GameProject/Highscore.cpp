#include "Highscore.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "Level1.h"

Highscore::Highscore( )
{
	m_bNothingTyped = true;
	m_sUsername = "Type in username";
	m_iScrollPos = 10;
	m_iMaxScrollPos = 100;
	m_iMinScrollPos = 10;
	m_iScore = 10000;
	m_bSubmitted = false;
}

Highscore::Highscore( short score )
{
	m_bNothingTyped = true;
	m_sUsername = "Type in username";
	m_iScrollPos = 10;
	m_iMaxScrollPos = 100;
	m_iMinScrollPos = 10;
	m_iScore = score;
	m_bSubmitted = false;
}

void Highscore::loadContent( )
{
	sf::View tempView = StateHandler::getInstance().m_pWindow -> getDefaultView();

	StateHandler::getInstance().m_pWindow -> setView(tempView);

	decodeJson( );

	if( !m_font.loadFromFile( "../../Resources/SourceCodePro-Black.ttf" ) ) //Load font 
	{
		std::cout << "Could not load font" << std::endl;
	}
	else
	{
		m_usernameText.setString( m_sUsername );
		m_usernameText.setPosition( 300, 625 );
		m_usernameText.setFont( m_font );

		m_submitErrorText.setString( "" );
		m_submitErrorText.setPosition( 300, 700 );
		m_submitErrorText.setFont( m_font );

		m_userScore.setString("Your score: " + std::to_string((long long) m_iScore));
		m_userScore.setPosition(250, 100); 
		m_userScore.setFont( m_font );

		reloadLeaderboard( );
	}

	if( !m_backgroundTexture.loadFromFile("../../Resources/highscores_background.PNG" ) )
	{
		std::cout << "Could not load highscores_background.PNG" << std::endl;
	}
	else
	{
		m_backgroundSprite.setTexture( m_backgroundTexture );
		m_backgroundSprite.setPosition( 0, 0 );
	}

	if( !m_mainMenuTexture.loadFromFile("../../Resources/main_menu_button.PNG" ) )
	{
		std::cout << "Could not load main_menu_button.PNG" << std::endl;
	}
	else
	{
		m_mainMenuSprite.setTexture( m_mainMenuTexture );
		m_mainMenuSprite.setPosition( 950, 25 );
	}

	if( !m_mainMenuPressTexture.loadFromFile("../../Resources/main_menu_button_pressed.PNG" ) )
	{
		std::cout << "Could not load main_menu_button_pressed.PNG" << std::endl;
	}

	if( !m_submitTexture.loadFromFile("../../Resources/submit_button.PNG" ) )
	{
		std::cout << "Could not load submit_button.PNG" << std::endl;
	}
	else
	{
		m_submitSprite.setTexture( m_submitTexture );
		m_submitSprite.setPosition( 700, 600 );
	}

	if( !m_submitPressTexture.loadFromFile("../../Resources/submit_button_pressed.PNG" ) )
	{
		std::cout << "Could not load submit_button_pressed.PNG" << std::endl;
	}

	if( !m_textFieldTexture.loadFromFile("../../Resources/submit_field.PNG" ) )
	{
		std::cout << "Could not load submit_field.PNG" << std::endl;
	}
	else
	{
		m_textFieldSprite.setTexture( m_textFieldTexture );
		m_textFieldSprite.setPosition( 275, 600 );
	}
}


void Highscore::reloadLeaderboard( )
{
	std::string leaderboardText = "";

	for( int i = m_iScrollPos - m_iMinScrollPos; ( i < leaderboard.size( ) ) && ( i < m_iScrollPos ); i++ )
	{
		std::ostringstream tempString;
		std::string number = std::to_string( ( long long ) i + 1 );
		number += ".";
		tempString	<< std::left
					<< std::setw(5)	 			<< number
					<< std::setw(15)			<< leaderboard[i].name		
					<< std::setw(10)			<< leaderboard[i].score		
					<< '\n';
		leaderboardText += tempString.str();
	}

	m_leaderboardText.setString( leaderboardText );
	m_leaderboardText.setPosition( 350, 160 );
	m_leaderboardText.setCharacterSize( 35 );
	m_leaderboardText.setFont( m_font );
}

void Highscore::unloadContent( )
{

}

void Highscore::update( )
{

}

void Highscore::processEvents( sf::Event event )
{
	if ( event.type == sf::Event::TextEntered )
	{
		if ( event.text.unicode )
		{
			if ( m_bNothingTyped )
			{
				m_sUsername.resize ( m_sUsername.size( ) - m_sUsername.size( ) );
				m_bNothingTyped = false;
			}
			if ( m_sUsername.size() < 15 )
			{
				m_sUsername += ( event.text.unicode );
			}
			m_usernameText.setString( m_sUsername );
		}
	}

	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Back ) )
	{
		if ( m_bNothingTyped )
		{
			m_sUsername.resize ( m_sUsername.size( ) - m_sUsername.size( ) );
			m_bNothingTyped = false;
		}

		if ( m_sUsername.size( ) > 0 ) 
		{
			m_sUsername.resize ( m_sUsername.size( ) - 1 );
			
		}
		m_usernameText.setString( m_sUsername );
	}

	if ( event.type == sf::Event::MouseWheelMoved  )
	{
		if( event.mouseWheel.delta == 1)
		{
			 m_iScrollPos--;
		}
		else if( event.mouseWheel.delta == -1)
		{
			m_iScrollPos++;
		}

		if( m_iScrollPos < m_iMinScrollPos )
		{
			m_iScrollPos = m_iMinScrollPos;
		}

		if( m_iScrollPos > leaderboard.size() )
		{
			m_iScrollPos = leaderboard.size();
		}

		if( m_iScrollPos > m_iMaxScrollPos )
		{
			m_iScrollPos = m_iMaxScrollPos;
		}

		reloadLeaderboard( );
	}

	if ((	event.mouseMove.x >= m_mainMenuSprite.getPosition().x && event.mouseMove.x <= m_mainMenuSprite.getPosition().x+400 && 
			event.mouseMove.y >= m_mainMenuSprite.getPosition().y && event.mouseMove.y <= m_mainMenuSprite.getPosition().y+100)) 
	{
		m_mainMenuSprite.setTexture(m_mainMenuPressTexture);
	}
	else
	{
		m_mainMenuSprite.setTexture(m_mainMenuTexture);
	}

	if(		event.mouseButton.x >=  m_mainMenuSprite.getPosition().x && event.mouseButton.x <=  (m_mainMenuSprite.getPosition().x+270) && 
			event.mouseButton.y >=  m_mainMenuSprite.getPosition().y && event.mouseButton.y <=  m_mainMenuSprite.getPosition().y+70)
	{
		StateHandler::getInstance().m_AudioManager.stopOrResumeMusic();
		StateHandler::getInstance().setMenuShield(true);
	}

	if ((	event.mouseMove.x >= m_submitSprite.getPosition().x && event.mouseMove.x <= m_submitSprite.getPosition().x+400 && 
			event.mouseMove.y >= m_submitSprite.getPosition().y && event.mouseMove.y <= m_submitSprite.getPosition().y+100)) 
	{
		m_submitSprite.setTexture(m_submitPressTexture);	
	}
	else
	{
		m_submitSprite.setTexture(m_submitTexture);
	}

	if(		event.mouseButton.x >=  m_submitSprite.getPosition().x && event.mouseButton.x <=  m_submitSprite.getPosition().x+270 && 
			event.mouseButton.y >=  m_submitSprite.getPosition().y && event.mouseButton.y <=  m_submitSprite.getPosition().y+70)
	{
		checkInput();
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		checkInput();
	}

	if( sf::Keyboard::isKeyPressed(sf::Keyboard::Escape ))
	{
		if(!StateHandler::getInstance().getMenuShield())
		{
			StateHandler::getInstance().setMenuShield(true);
		}
	}
}

void Highscore::draw( )
{
	m_window = StateHandler::getInstance().m_pWindow;

	m_window->draw( m_backgroundSprite );
	m_window->draw( m_mainMenuSprite );
	m_window->draw( m_submitSprite );
	m_window->draw( m_textFieldSprite );
	m_window->draw( m_usernameText );
	m_window->draw( m_leaderboardText );
	m_window->draw( m_submitErrorText );
	m_window -> draw( m_userScore );
}

void Highscore::decodeJson( )
{
	m_sJson = httpGet( "www.game-details.com", "/corrupted/highscorescore.php" );

	const char* file_name( "json_example.txt" );

	mValue value;
	read( m_sJson, value );

	m_sJson = write( value, pretty_print );

	std::ofstream fs;
		
	fs.open( file_name ); 

	if( !fs )
	{
		std::cerr<<"Cannot open the output file."<<std::endl;
	}
	else
	{
		fs << m_sJson;
		fs.close( );
	}

	leaderboard = read_entries( file_name );		
}

std::string Highscore::httpGet( std::string host, std::string path )
{
	sf::Http Http;

	Http.setHost( host );

	sf::Http::Request Request;
	Request.setMethod( sf::Http::Request::Get );
	Request.setUri( path );
	Request.setBody( "" );
	Request.setHttpVersion( 1, 0 );

	// Send it and get the response returned by the server
	std::cout << "Loading leaderboards...Please wait" << std::endl;
	sf::Http::Response Page = Http.sendRequest( Request );

	// Display the response
	if( Page.getStatus(  ) == 200 )
	{
		std::cout<<"\nSuccessfully loaded!"<< std::endl;
	}
	//std::cout << Page.getBody( ) << std::endl;

	return Page.getBody( );
}

Highscore::User Highscore::read_user( const mObject& obj  )
{
	User user;

	user.name  = find_value( obj, "name" ).get_str( );
	user.score = find_value( obj, "score" ).get_str( );

	return user;
}

const mValue& Highscore::find_value( const mObject& obj, const std::string& name  )
{
	mObject::const_iterator i = obj.find( name );

	assert( i != obj.end( ) );
	assert( i->first == name );

	return i->second;
}

std::vector< Highscore::User > Highscore::read_entries( const char* file_name )
{
	std::ifstream is( file_name );

	mValue value;

	read( is, value );

	const mArray& user_array = value.get_array( );

	std::vector< User > users;

	for( std::vector< User >::size_type i = 0; i < user_array.size( ); ++i )
	{
		users.push_back( read_user( user_array[i].get_obj( ) ) );
	}

	return users;
}

void Highscore::write_user( mArray& a, const Highscore::User& user )
{
	mObject user_obj;

	user_obj[ "name"  ] = user.name;
	user_obj[ "score" ] = user.score;

	a.push_back( user_obj );
}

bool Highscore::isalnumch(char ch) {
	return ( (	(ch >= 'a' && ch <= 'z')	|| 
				(ch >= 'A' && ch <= 'Z'))	||
				(ch >= '0' && ch <= '9') );
}

bool Highscore::isalnumstr(std::string str) 
{
	for (std::string::iterator it = str.begin(); it != str.end(); it++) 
	{
		if (!isalnumch((char)*it))
		{
			return 0;
		}
	}       
	return 1;
}

void Highscore::checkInput()
{
	if(isalnumstr(m_sUsername) && m_sUsername != "Type in username" && m_bSubmitted == false && m_iScore > 0)
	{
		if(m_sUsername.size() > 0)
		{
			m_submitErrorText.setString("Submitting score...please wait");
			std::string score = std::to_string((long long)m_iScore);
			std::string path = "/corrupted/insertscore.php?name=" + m_sUsername + "&score=" + score;
			httpGet("www.game-details.com", path );
			m_submitErrorText.setString("Success!");
			m_bSubmitted = true;
			decodeJson();
			reloadLeaderboard( );
		}
	}
	else
	{
		m_submitErrorText.setString("Please enter a valid username before submitting");
	}
}