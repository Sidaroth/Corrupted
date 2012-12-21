#include "KeyboardController.h"



KeyboardController::~KeyboardController()
{
	delete player;
}

KeyboardController::KeyboardController(Player* player_recieved,sf::RenderWindow* window_recieved){
	

	
	//KeyBinding (We will have to change it so instead of being hardcoded it will be read from a file.
	window = window_recieved;
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
	//audio_manager.loadAudio();
}


void KeyboardController::checkMouse(sf::Event event)
{
	if (mouseNotInUi(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if( event.mouseButton.button == sf::Mouse::Right )
			{
				//sf::View tempView = StateHandler::getInstance().m_pWindow->getView();

				//int windowX = tempView.getCenter( ).x - ( tempView.getSize( ).x / 2 );
				//int windowY = tempView.getCenter( ).y - ( tempView.getSize( ).y / 2 );

				Vector2f mouseCoordinates;
				//Vector2f * playerCoordinates = player -> getPosition();
				mouseCoordinates.x = event.mouseButton.x;// + ( playerCoordinates -> x );// + windowX;
				mouseCoordinates.y = event.mouseButton.y;// + ( playerCoordinates -> y );// + windowY;

				std::cout << "\nX: " << mouseCoordinates.x << "\nY: " << mouseCoordinates.y << std::endl;

				player -> castSpell( mouseCoordinates, 0 );
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				//std::cout << "the left button was pressed" << std::endl;
				//std::cout << "mouse x: " << event.mouseButton.x << std::endl;
				//std::cout << "mouse y: " << event.mouseButton.y << std::endl;
		
				//Calculate direction of the attack

				sf::Vector2i mouse_position;
		
				mouse_position.x = event.mouseButton.x;
				mouse_position.y = event.mouseButton.y;
	
				Vector2f* v2f_player_position;
				v2f_player_position = player -> getSpritePosition();
			
				v2f_player_position -> x = (window->getSize().x / 2) + 46;
				v2f_player_position -> y = (window->getSize().y / 2) + 46;
				//1366/2, 768/2
	
				Vector2f* v2f_attack_direction = new Vector2f();
				float angle = atan2( ( v2f_player_position->y - mouse_position.y ), ( v2f_player_position->x - mouse_position.x ) );
		
				int i_attack_direction = 0;
		
				// isn't there a better way to do this marti?
				if ((angle > 0) && (angle <= 0.3925))
				{
					i_attack_direction = 6;
				}
				else if ((angle > 0.3925) && (angle <= 1.1775))
				{
					i_attack_direction = 7;
				}
				else if ((angle > 1.1775) && (angle <= 1.9625))
				{
					i_attack_direction = 0;
				}
				else if ((angle > 1.9625) && (angle <= 2.7475))
				{
					i_attack_direction = 1;
				}
				else if ((angle > 2.7475) && (angle <= 3.14))
				{
					i_attack_direction = 2;
				}
				else if ((angle <= 0) && (angle > -0.3925))
				{
					i_attack_direction = 6;
				}
				else if ((angle <= -0.3925) && (angle > -1.1775))
				{
					i_attack_direction = 5;
				}
				else if ((angle <= -1.1775) && (angle > -1.9625))
				{
					i_attack_direction = 4;
				}
				else if ((angle <= -1.9625) && (angle > -2.7475))
				{
					i_attack_direction = 3;
				}
				else if ((angle <= -2.7475) && (angle > -3.14))
				{
					i_attack_direction = 2;
				}

				//End calculate direction

				if (player -> attack(i_attack_direction)) ///0=N, 1=NE, 2=E, 3=SE, 4=S, 5=SW, 6=W, 7=NW
				{
					if (player -> checkAttackCollision(i_attack_direction))
					{
						audio_manager.playSound("attack_hit");
					}

					else
					{
						audio_manager.playSound("attack_miss");
					}
				}
			}
		}
	}
}

void KeyboardController::checkPressed()
{
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
	
	}
}

bool KeyboardController::mouseNotInUi(sf::Event event)
{
	if (event.mouseButton.x < 290 && event.mouseButton.y > 575)
	{
		return false;
	}

	if (event.mouseButton.x > 440 && event.mouseButton.x < 925 && event.mouseButton.y > 670)
	{
		return false;
	}

	if (event.mouseButton.x > 1075 && event.mouseButton.y > 575)
	{
		return false;
	}

	return true;
}