#include "KeyboardController.h"



KeyboardController::KeyboardController(Player* player_recieved){

	//KeyBinding (We will have to change it so instead of being hardcoded it will be read from a file.

	player = player_recieved;
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
	 if(!player->isDoingAction()){
	//0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
	//MOVEMENT


	if (sf::Keyboard::isKeyPressed(Keys["foward"].myKeyCode))
	{
		if (sf::Keyboard::isKeyPressed(Keys["right"].myKeyCode)){
			//std::cout << "UP-RIGHT pressed" << std::endl;
			player->move( player -> NORTH_EAST );
		}else if(sf::Keyboard::isKeyPressed(Keys["left"].myKeyCode)){
			//std::cout << "UP-LEFT" << std::endl;
			player->move( player -> NORTH_WEST );
		}else{
			//std::cout << "UP pressed" << std::endl;
			player->move( player -> NORTH );
		}
	}else if(sf::Keyboard::isKeyPressed(Keys["backward"].myKeyCode))
	{
		if (sf::Keyboard::isKeyPressed(Keys["right"].myKeyCode)){
			//std::cout << "DOWN-RIGHT" << std::endl;
			player->move( player -> SOUTH_EAST );
		}else if(sf::Keyboard::isKeyPressed(Keys["left"].myKeyCode)){
			//std::cout << "DOWN LEFT" << std::endl;
			player->move( player -> SOUTH_WEST);
		}else{
			//std::cout << "DOWN pressed" << std::endl;
			player->move( player -> SOUTH );
		}
	}else
	{
		if (sf::Keyboard::isKeyPressed(Keys["right"].myKeyCode)){
			//std::cout << "RIGHT pressed" << std::endl;
			player->move( player -> EAST );
		}
		if (sf::Keyboard::isKeyPressed(Keys["left"].myKeyCode)){
			//std::cout << "LEFT pressed" << std::endl;
			player->move( player -> WEST );
		}
	}
	
	
	//OTHER ACTIONS
	if (sf::Keyboard::isKeyPressed(Keys["skill_1"].myKeyCode))
	{
		//std::cout << "Space pressed" << std::endl;
	}
	if(sf::Mouse::isButtonPressed(Keys["shoot" ].myMouseButton)){
		std::cout << "Mouse left pressed" << std::endl;
		
		//Calculate direction of the atack

		sf::Vector2i v_mouse_position;
		v_mouse_position = sf::Mouse::getPosition();
	
		std::cout << "Position X: " << v_mouse_position.x << " Position Y: " << v_mouse_position.y << std::endl;
		Vector2f* v2f_player_position;
		v2f_player_position = player->getSpritePosition();

		v2f_player_position->x=1366/2;
		v2f_player_position->y=768/2;
		//1366/2, 768/2
		std::cout << " PLAYER Position X: " << v2f_player_position->x << "PLAYER  Position Y: " << v2f_player_position->y << std::endl;
		Vector2f* v2f_atack_direction = new Vector2f();
		float angle = atan2((v2f_player_position->y-v_mouse_position.y),(v2f_player_position->x-v_mouse_position.x));
		/*v2f_atack_direction->x = (v2f_player_position->x - v_mouse_position.x);
		v2f_atack_direction->y = (v2f_player_position->y - v_mouse_position.y);*/

		

		std::cout << "Angle: " << angle << std::endl;
		
		int i_atack_direction=0;
		
		if((angle>0)&&(angle<=0.3925)){
			std::cout << "Atacking WEAST" << std::endl;
			i_atack_direction=6;
		}else if((angle>0.3925)&&(angle<=1.1775)){
			i_atack_direction=7;
			std::cout << "ATACKING NORTH-WEAST" << std::endl;
		}else if((angle>1.1775)&&(angle<=1.9625)){
			i_atack_direction=0;
			std::cout << "ATACKING NORTH" << std::endl;
		}else if((angle>1.9625)&&(angle<=2.7475)){
			i_atack_direction=1;
			std::cout << "ATACKING NORTH-EAST" << std::endl;
		}else if((angle>2.7475)&&(angle<=3.14)){
			i_atack_direction=2;
			std::cout << "ATACKING EAST" << std::endl;
		}else if((angle<=0)&&(angle>-0.3925)){
			std::cout << "Atacking WEAST" << std::endl;
			i_atack_direction=6;
		}else if((angle<=-0.3925)&&(angle>-1.1775)){
			i_atack_direction=5;
			std::cout << "ATACKING SOUTH-WEAST" << std::endl;
		}else if((angle<=-1.1775)&&(angle>-1.9625)){
			i_atack_direction=4;
			std::cout << "ATACKING SOUTH" << std::endl;
		}else if((angle<=-1.9625)&&(angle>-2.7475)){
			i_atack_direction=3;
			std::cout << "ATACKING SOUTH-EAST" << std::endl;
		}else if((angle<=-2.7475)&&(angle>-3.14)){
			i_atack_direction=2;
			std::cout << "ATACKING EAST" << std::endl;
		}

		//End calculate direction

		player->attack(i_atack_direction); ///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
	}
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
		std::cout << "Mouse Right pressed" << std::endl;
		player->changeAnimationToWalk();
	}

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
			std::cout << "I don't know how to read files?...!" << std::endl;
		}

	return true;
}
