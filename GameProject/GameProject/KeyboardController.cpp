#include "KeyboardController.h"


KeyboardController::KeyboardController (Player* player, sf::RenderWindow* window)
{
	m_Window = window;
	m_Player = player;
}

KeyboardController::~KeyboardController()
{
	delete m_Player;
}


void KeyboardController::mouseInput(sf::Event event)
{
	if (mouseNotInUi(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if ( event.mouseButton.button == sf::Mouse::Right )
			{

				Vector2f mouseCoordinates;

				mouseCoordinates.x = event.mouseButton.x;
				mouseCoordinates.y = event.mouseButton.y;

				m_Player -> castSpell( mouseCoordinates, 0 );
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				sf::Vector2i mousePosition;
		
				mousePosition.x = event.mouseButton.x;
				mousePosition.y = event.mouseButton.y;
	
				Vector2f* playerPosition;
				playerPosition = m_Player -> getSpritePosition();
			
				playerPosition -> x = (m_Window->getSize().x / 2) + 46;
				playerPosition -> y = (m_Window->getSize().y / 2) + 46;
	
				float angle = atan2( ( playerPosition->y - mousePosition.y ), ( playerPosition->x - mousePosition.x ) );
		
				int attackDirection = 0;
		
				// isn't there a better way to do this?
				if ((angle > 0) && (angle <= 0.3925))
				{
					attackDirection = 6;
				}
				else if ((angle > 0.3925) && (angle <= 1.1775))
				{
					attackDirection = 7;
				}
				else if ((angle > 1.1775) && (angle <= 1.9625))
				{
					attackDirection = 0;
				}
				else if ((angle > 1.9625) && (angle <= 2.7475))
				{
					attackDirection = 1;
				}
				else if ((angle > 2.7475) && (angle <= 3.14))
				{
					attackDirection = 2;
				}
				else if ((angle <= 0) && (angle > -0.3925))
				{
					attackDirection = 6;
				}
				else if ((angle <= -0.3925) && (angle > -1.1775))
				{
					attackDirection = 5;
				}
				else if ((angle <= -1.1775) && (angle > -1.9625))
				{
					attackDirection = 4;
				}
				else if ((angle <= -1.9625) && (angle > -2.7475))
				{
					attackDirection = 3;
				}
				else if ((angle <= -2.7475) && (angle > -3.14))
				{
					attackDirection = 2;
				}

				if(m_Player->attack(attackDirection))
				{
					if (m_Player->checkAttackCollision(attackDirection))
					{
						StateHandler::getInstance().m_AudioManager.playSound("attack_hit");
					}
					else
					{
						StateHandler::getInstance().m_AudioManager.playSound("attack_miss");
					}
				}
			}
		}
	}
}

void KeyboardController::keyboardInput()
{
	if (!m_Player->isDoingAction())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_Player->move( m_Player -> NORTH_EAST );
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_Player->move( m_Player -> NORTH_WEST );
			}

			else
			{
				m_Player->move( m_Player -> NORTH );
			}
		}

		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_Player->move( m_Player -> SOUTH_EAST );
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_Player->move( m_Player -> SOUTH_WEST );
			}

			else
			{
				m_Player->move( m_Player -> SOUTH );
			}
		}

		else
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				m_Player->move( m_Player -> EAST );
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				m_Player->move( m_Player -> WEST );
			}
		}

		if( sf::Keyboard::isKeyPressed(sf::Keyboard::Num1 ) )
		{
			m_Player->heal();
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