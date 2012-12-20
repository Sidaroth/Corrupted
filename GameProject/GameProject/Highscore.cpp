#include "Highscore.h"

// TEMPORARY!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#include "TitleScreen.h"
#include "Level1.h"

Highscore::Highscore( )
{
	m_sUsername = "";
}

void Highscore::loadContent( sf::RenderWindow* window )
{
	

	if(!m_impactFont.loadFromFile("../../Resources/impact.ttf"))				//Load font 
	{
		std::cout << "Could not load font" << std::endl;
	}
	else
	{
		std::cout << "stringstart";
		m_usernameText.setString(m_sUsername);
		m_usernameText.setPosition(1085, 583);
		m_usernameText.setScale(0.6, 0.6);
		m_usernameText.setFont(m_impactFont);
		std::cout << "stringend";
	}

decodeJson( );
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
			m_sUsername += ( event.text.unicode );
			m_usernameText.setString( m_sUsername );
		}
	}
	if( sf::Keyboard::isKeyPressed( sf::Keyboard::Back ) )
	{
		if ( m_sUsername.size ( ) > 0 )  m_sUsername.resize ( m_sUsername.size ( ) - 1 );
	}
}

void Highscore::draw( )
{
	m_pWindow->draw( m_backgroundSprite );
	StateHandler::getInstance().m_pWindow->draw(m_usernameText);
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