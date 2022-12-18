/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "FrameTimer.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	FrameTimer ft;
	Board brd;
	Location starting_loc = { 2,2 };
	Snake snek;
	std::mt19937 rng;
	Location delta_loc = { 1,0 };
	static constexpr float snekMovePeriodMin = 0.08f;
	float snekMovePeriod = 0.4f;
	static constexpr float snekMovePeriodSpeedUp = 0.15f;
	static constexpr float snekSpeedUpFactor = 0.02f;
	static constexpr int nPoison = 150;
	static constexpr int nObstacle = 15;
	int nFood = 5;
	int nEatenFood = 0;
	float snekMoveCounter = 0.0f;
	bool gameIsOver = false;
	bool gameIsStarted = false;
	bool up = false;
	bool down = false;
	bool right = false;
	bool left = false;
	/********************************/
	/*  User Variables              */
	/********************************/
};