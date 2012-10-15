#include "KeyboardController.h"



KeyboardController::KeyboardController(){

	//KeyBinding


	MyKeys key;
	//Binding the left mouse button to the "Shoot" action
	key.myInputType = MouseInput;
	key.myEventType = sf::Event::MouseButtonPressed;
	key.myMouseButton = sf::Mouse::Left;
	Keys["shoot"] = key;
	//Binding the Space key to the "skill1" action
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	//key.myKeyCode = sf::Key::Return;
	key.myKeyCode = sf::Keyboard::Space;
	Keys["skill_1"] = key;
	//Let's bind the A key to the "Left" action
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::A;
	Keys["left"] = key;
	//Let's bind the D key to the "Right" action
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::D;
	Keys["right"] = key;
	//Let's bind the W key to the "Fowards" action
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::W;
	Keys["foward"] = key;
	//Let's bind the S key to the "Backwards" action
	key.myInputType = KeyboardInput;
	key.myEventType = sf::Event::KeyPressed;
	key.myKeyCode = sf::Keyboard::S;
	Keys["backward"] = key;
	//EndKeyBinding

	
	std::cout << "Keyboard controller created" << std::endl;
	//loadXML();

}

void KeyboardController::checkPressed(){
	 

	if (sf::Keyboard::isKeyPressed(Keys["foward"].myKeyCode))
	{
		std::cout << "Move UP" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(Keys["backward"].myKeyCode))
	{
		std::cout << "Move DOWN" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(Keys["left"].myKeyCode))
	{
		std::cout << "Move LEFT" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(Keys["right"].myKeyCode))
	{
		std::cout << "Move RIGHT" << std::endl;
	}
	if (sf::Keyboard::isKeyPressed(Keys["skill_1"].myKeyCode))
	{
		std::cout << "Space pressed" << std::endl;
	}

}
	


bool KeyboardController::loadXML(){

	tinyxml2::XMLDocument doc;

		bool loadOkay=doc.LoadFile( "../KeyActions.xml");
		
		if (loadOkay)
		{
			std::cout << "I loaded the file!" << std::endl;
			
			tinyxml2::XMLElement* titleElement = doc.FirstChildElement( "PLAY" )->FirstChildElement( "TITLE" );
			const char* title = titleElement->GetText();
			printf( "First element: %s\n", title );

			/*tinyxml2::XMLText* textNode = titleElement->FirstChild()->ToText();
			title = textNode->Value();
			printf( "Name of play (2): %s\n", title );
			//dump_to_stdout( &doc ); // defined later in the tutorial*/
		}
		else
		{
			std::cout << "I don't know how to read files, because I'm retarded !" << std::endl;
		}

	return true;
}
