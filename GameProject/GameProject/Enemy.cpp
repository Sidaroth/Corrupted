﻿#include "Enemy.h"


void Enemy::update()
{
	Character::update();

	animation();
	if(!m_bDead)
	{
		float xPos = m_Sprite.getPosition().x;
		float yPos = m_Sprite.getPosition().y;
		short quarterTile = TILESIZE / 4;

		pathLocation = m_Path.size() - 1;
		short direction = -1;

		if(pathLocation >= 0) // If there are any pathsteps. 
		{
			pathStep = m_Path[pathLocation];
			float stepX = pathStep -> x + quarterTile;		// Check for middle of tile. 
			float stepY = pathStep -> y + quarterTile;

			if((xPos + TILESIZE) < stepX)	// right side
			{
				direction = 2;			// east
			}
			else if(xPos > stepX)			// left side
			{
				direction = 6;			// West
			}
			else
			{
				xStepGoalReached = true;
			}

			if((yPos + TILESIZE) < stepY)	// bottom
			{
				if(direction == EAST)	
				{
					direction = SOUTH_EAST;		// south-East
				}
				else if(direction == WEST)	
				{
					direction = SOUTH_WEST;		// south-west
				}
				else
				{
					direction = SOUTH;		// south.
				}
			}
			else if(yPos > stepY)	// top 
			{
				if(direction == EAST)
				{
					direction = NORTH_EAST;  // north east
				}
				else if(direction == WEST)
				{
					direction = NORTH_WEST;	// north-west.
				}
				else
				{
					direction = NORTH;	// north
				}

			}
			else
			{
				yStepGoalReached = true;
			}

			if(direction != -1)
			{
				move(direction);
			}

			if(xStepGoalReached && yStepGoalReached)
			{
				m_Path.erase(m_Path.end() - 1);
				xStepGoalReached = false;
				yStepGoalReached = false;
			}
		}
		else
		{
			short attackGoalX = m_pPlayerPos -> x + quarterTile;
			short attackGoalY = m_pPlayerPos -> x + quarterTile;

			// if coming from the left, and within attackRange.
			if(xPos < attackGoalX && abs((xPos + TILESIZE) - (attackGoalX)) < m_fAttackRange)
			{
				m_bTryAttack = true;
			}
			else if(xPos >= attackGoalX && abs((xPos) - (attackGoalX)) < m_fAttackRange)	// Coming from the right
			{
				m_bTryAttack = true;
			}
			else if(yPos < attackGoalY && abs((yPos + TILESIZE) - (attackGoalY)) < m_fAttackRange)	// From above.
			{
				m_bTryAttack = true;
			}
			else if(yPos >= attackGoalY && abs((yPos) - (attackGoalY)) < m_fAttackRange)		// From below. 
			{
				m_bTryAttack = true;
			}
			else	// Not within range. 
			{
				m_bTryAttack = false;
				findPath(xPos, yPos, m_pPlayerPos -> x, m_pPlayerPos -> y);
			}

			if(m_bTryAttack)
			{
				m_Sprite.setTexture((*m_TextureTypes[ATTACK]));
				m_bDoingAction = true;
			}
		}
	}
}

bool Enemy::hasAttacked()
{
	if(m_bTryAttack && m_shFrameCount % 60 == 0 && m_shBitmapCol > 5)
	{
		//std::cout << "attack!\n";
		m_bAttacked = true;
	}
	else
	{
		//std::cout << "Don't attack!!\n";
		m_bAttacked = false;
	}

	return (m_bTryAttack && m_bAttacked);
}

void Enemy::stopAttack()
{
	m_bTryAttack = false;
	m_bAttacked = false;
}

/// Sets the collision map for the enemy, and the width and height of the world. Refers to memory address of the map inside the environment. 
void Enemy::setCollisionMap(std::vector<bool>* collisionMap, int horizontalSize)
{
	m_HorizontalBitmapSize = horizontalSize;
	m_VerticalBitmapSize = collisionMap -> size() / horizontalSize;
	this -> collisionMap = collisionMap;
}

/// Checks to see if the enemy is dead, and has finished it's death animation.
bool Enemy::isDead()
{
	return(m_bDead && stopAnimation);
}

/// adds 10 for orthogonal movement, 14 for diagonal. Precalculating this avoids any 
/// decimal and square root calculations during runtime. The pythagorean theorem states that 
/// c^2 = b^2 + a^2, giving c = sqroot(1^2 + 1^2) = sqroot(2) as the answer.
/// The square root of 2 is 1.414, hence 14. 
#define ORTHOGONAL_MOVEMENT_COST 10;	// Orthogonal == horizontal || vertical. 
#define DIAGONAL_MOVEMENT_COST 14;

	/*!
	 Pathfinding algorithm (A*) using a Binary Heap representation of the openList. 

	 Given a tileset:
	 | 0,0 | 1,0 | 2,0 | 3,0 | 4,0 |
	 | 0,1 | 1,1 | 2,1 | 3,1 | 4,1 |
	 | 0,2 | 1,2 | 2,2 | 3,2 | 4,2 |
	 | 0,3 | 1,3 | 2,3 | 3,3 | 4,3 |
	 | 0,4 | 1,4 | 2,4 | 3,4 | 4,4 |
	 
	 Represented as a 1D array this will look like (Row0 Row1 Row2 Row3 etc.)
	 (0,0), (1,0), (2,0), (3,0), (4,0), (0,1), (1,1), (2,1), (3,1), (4,1), (0,2), (1,2), (2,2), (3,2), (4,2), (0,3), (1,3), (2,3), (3,3), (4,3), (0,4), (1,4), (2,4), (3,4), (4,4) 

	 We can find the coordinate position in the array by doing (row * horizontalSize + column).
	 Example1: if the position we want is (2, 1) we can find it in the array by doing 1 * 5 + 2 = 7 (For humans this would be 8, but as programmers we count from 0)
	 Example2: if the position we want is (3, 0) we can find it in the array by doing 0 * 5 + 3 = 3 (For humans this would be 4, but as programmers we count from 0)
	 Example3: if the position we want is (3, 4) we can find it in the array by doing 4 * 5 + 3 = 23 (For humans this would be 24, but as programmers we count from 0)

	*/

short Enemy::findPath(int startX, int startY, int goalX, int goalY)
{
	m_Path.erase(m_Path.begin(), m_Path.end()); // Remove the old stuff...

	//std::cout << "recalculating...\n";
	const short NUMBER_OF_TILES_TO_CHECK = 30;
	m_Path.reserve(NUMBER_OF_TILES_TO_CHECK);

	path = UNDETERMINED;

	goalTileX = goalX / TILESIZE;
	goalTileY = goalY / TILESIZE;
	startX = startX / TILESIZE;
	startY = startY / TILESIZE;

	parentXval = 0;
	parentYval = 0;

	if(goalTileX == startX && goalTileY == startY)
	{
		//std::cout << "path already...\n";
		path = FOUND;
	}

	bool placeInHeapFound = false;
	whichList[goalTileX][goalTileY] = 0;

	short temp = 0;
	short insertPosition = 0;
	short numberOfClosedListItems = 1;	// Number of items currently in the closed list
	short currentPos = 0;				// Current position in collision vector (1D)

	bool goalReached = false;

	short tempX;
	short pathX;
	short pathY;
	

	short v = 1;
	short u = v;

	onClosedList = onClosedList + 2;		// changing the values of these is faster than constantly resetting whichList to 0. 
	onOpenList = onClosedList - 1;

	if(onClosedList > 100000)		// reset whichList occasionaly. 
	{
		for(int i = 0; i < m_VerticalBitmapSize; i++)
		{
			for(int j = 0; j < m_HorizontalBitmapSize; j++)
			{
				whichList[i][j] = 0;
			}
			onClosedList = 10;
		}
	}

	openList[1] = 1;
	openX[1] = startX;
	openY[1] = startY;
	gCost[startX][startY] = 0;

	squaresChecked = 0;
	tilesChecked = 0;
	numberOfOpenListItems = 1;

	//initializePathFind();

	while(path == UNDETERMINED /*&& tilesChecked < NUMBER_OF_TILES_TO_CHECK*/)
	{
		//std::cout << tilesChecked << "\n";
		if(numberOfOpenListItems != 0)
		{
			// Deleting & Selecting
			parentXval = openX[openList[1]];
			parentYval = openY[openList[1]];
		
			whichList[parentXval][parentYval] = onClosedList;

			openList[1] = openList[numberOfOpenListItems];
			numberOfOpenListItems--;

			//selectFromOpenList();
			placeInHeapFound = false;

			v = 1;
						
			while(!placeInHeapFound)			// Find the place in the heap for the element we moved. 
			{
				u = v;

				if(2 * u + 1 <= numberOfOpenListItems)	// if both children exists. 
				{
					if(fCost[openList[u]] >= fCost[openList[ 2 * u]])		// Check first child.
					{
						v = 2 * u;
					}
					
					if(fCost[openList[v]] >= fCost[openList[2 * u + 1]])	// Check second child.
					{
						v = 2 * u + 1;
					}
				}
				else if(2 * u <= numberOfOpenListItems)	// If only 1 child.
				{
					if(fCost[openList[u]] >= fCost[openList[ 2 * u]])		// Check first child.
					{
						v = 2 * u;
					}
				}


				if(u != v)					// If 'v' was changed, a swap is needed.
				{
					temp = openList[u];
					openList[u] = openList[v];
					openList[v] = temp;
				}
				else
				{
					placeInHeapFound = true;
				}
			}
		
			// Deletion / selection end. 

			// Find and add neighbours to openList. 

			if(parentYval > 0 && parentYval < m_VerticalBitmapSize)
			{
				for(int row = parentYval - 1; row <= parentYval + 1; ++row)
				{
					if(parentXval > 0 && parentXval < m_HorizontalBitmapSize)
					{
						for(int column = parentXval - 1; column <= parentXval + 1; ++column)
						{
							if( !(column == 0 && row == 0))	// If not self. 
							{
								if(whichList[column][row] != onClosedList)
								{
									currentPos = (row * m_HorizontalBitmapSize) + column;

									/*std::cout << "Parent: " << parentXval << ", " << parentYval << std::endl;
									std::cout << "column, row: " << column << ", " << row << std::endl;
									std::cout << "collisionPos: " << currentPos << std::endl;*/

									if( (*collisionMap)[currentPos] )	// If walkable
									{
										if(whichList[column][row] != onOpenList)	// If it hasn't been checked before. 
										{
											//insertIntoOpenList(column, row);
											temp = 0;
											insertPosition = 0;
	
											++squaresChecked;
											insertPosition = numberOfOpenListItems + 1;
											openList[insertPosition] = squaresChecked;
											openX[squaresChecked] = column;
											openY[squaresChecked] = row;


											// Figure ut Gcost
																	// If diagonal move
											if(abs(column - parentXval) == 1 && abs(row - parentYval) == 1)
											{
												temp = DIAGONAL_MOVEMENT_COST; 
											}
											else	// Orthogonal
											{
												temp = ORTHOGONAL_MOVEMENT_COST;
											}

											gCost[column][row] = gCost[parentXval][parentYval] + temp;

											// HCost & FCost
											fCost[openList[insertPosition]] = gCost[column][row] + (abs(column + goalTileX) + abs(row + goalTileY)) * ORTHOGONAL_MOVEMENT_COST;

											parentX[column][row] = parentXval;
											parentY[column][row] = parentYval;
	
											while(insertPosition > 1)		// While the new insert Has not reached the top. 
											{
												// Check if child is <= parent, if so, swap.
												if(fCost[openList[ insertPosition ]] <= fCost[openList[ insertPosition / 2 ]])
												{
													temp = openList[ insertPosition / 2 ];
													openList[ insertPosition / 2 ] = openList[ insertPosition ];
													openList[insertPosition] = temp;
				
													insertPosition = insertPosition / 2;
												}
												else
												{
													insertPosition = 0;
												}
											}

											++numberOfOpenListItems;
											// Change whichlist to show that the new item is on the openList. 
											whichList[column][row] = onOpenList;
										}
										else	// If it is already on the openList.
										{
											// Figure ut Gcost
											// If diagonal move
											if(abs(column - parentXval) == 1 && abs(row - parentYval) == 1)
											{
												temp = DIAGONAL_MOVEMENT_COST; 
											}
											else	// Orthogonal
											{
												temp = ORTHOGONAL_MOVEMENT_COST;
											}

											temp = gCost[parentXval][parentYval] + temp;

											if(temp < gCost[column][row])	// If it has found a shorter path. 
											{
												parentX[column][row] = parentXval;
												parentY[column][row] = parentYval;
												gCost[column][row] = temp;

												// We have to change it's position in the heap, meaning we have to find it, then recalculate it's fCost, then move it to it's appropriate
												// position in the heap. This may stay the same, or it may change. 
												for(int i = 1; i <= numberOfOpenListItems; i++)
												{
													// Item found. 
													if(openX[openList[i]] == column && openY[openList[i]] == row)
													{
														// Recalculate
														fCost[openList[i]] = gCost[column][row] + (abs(openX[openList[i]] + goalTileX) + abs(openY[openList[i]] + goalTileY)) * ORTHOGONAL_MOVEMENT_COST;

														insertPosition = i;

														while(insertPosition > 1)
														{
															// Check if child is < parent. If so swap. 
															if(fCost[openList[ insertPosition ]] < fCost[openList[ insertPosition / 2 ]])
															{
																temp = openList[insertPosition / 2];
																openList[insertPosition / 2] = openList[insertPosition];
																openList[insertPosition] = temp;
														
																insertPosition = insertPosition / 2;		// Going further up the heap. 
															}
															else
															{
																insertPosition = 0;	// step out of while. 
															}
														}

														i = numberOfOpenListItems + 2;	// break out of for. 
													}
												}
											}
										}
									}
								}
							}
						}	
					}
				}
			}
			++tilesChecked;
		}
		else
		{
			path = NONEXISTANT;
		}

		if(whichList[goalTileX][goalTileY] == onOpenList)	// on closed list
		{
			path = FOUND;
		}

	}

	if(path == FOUND)
	{
		pathX = goalTileX; 
		pathY = goalTileY;
		
		while(pathX != startX || pathY != startY)
		{
			pathStep = new Vector2f(pathX * TILESIZE, pathY * TILESIZE);
			m_Path.push_back(pathStep);
			
			tempX = parentX[pathX][pathY];
			pathY = parentY[pathX][pathY];
			pathX = tempX;
		}

		pathLength = m_Path.size();
	}
	
	return path;
}

Enemy::~Enemy()
{
	for(std::vector<Vector2f*>::iterator it = m_Path.begin(); it != m_Path.end();)
	{
		delete * it;			
		it = m_Path.erase(it);	// Erase returns a new iterator position, without it - it would create holes 
	}
}

/// Returns a pointer to the vector containing the projectiles "shot" by the enemy. 
std::vector<Projectile*>* Enemy::getProjectile( )
{
	return &m_vProjectiles;
}

/// Kills the enemy, plays the death animation, and returns the amount of souls (xp) to be given for the kill. 
short Enemy::kill()
{
	m_bDead = true;
	m_Sprite.setTexture( (*m_TextureTypes[DIE]));

	return m_shSoulsToDrop;
}