/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek(starting_loc)
{
	for (int i = 0; i < nPoison; i++)
	{
		brd.SpawnContents(rng, snek, Board::CellContents::Poison);
	}
	for (int i = 0; i < nFood; i++)
	{
		brd.SpawnContents(rng, snek, Board::CellContents::Food);
	}
	for (int i = 0; i < nObstacle; i++)
	{
		brd.SpawnContents(rng, snek, Board::CellContents::Obstacle);
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	if (gameIsStarted) {
		if (!gameIsOver)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP) && !down)
			{
				delta_loc = { 0,-1 };
				down = false;
				up = true;
				right = false;
				left = false;
			}
			else if (wnd.kbd.KeyIsPressed(VK_DOWN) && !up)
			{
				delta_loc = { 0,1 };
				down = true;
				up = false;
				right = false;
				left = false;
			}
			else if (wnd.kbd.KeyIsPressed(VK_LEFT) && !right)
			{
				delta_loc = { -1,0 };
				down = false;
				up = false;
				right = false;
				left = true;
			}
			else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && !left)
			{
				delta_loc = { 1,0 };
				down = false;
				up = false;
				right = true;
				left = false;
			}

			float snekModifiedMocePeriod = snekMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_CONTROL))
			{
				snekModifiedMocePeriod = std::min(snekMovePeriod, snekMovePeriodSpeedUp);
			}

			snekMoveCounter += dt;

			if (nEatenFood == 20)
			{
				gameIsStarted = false;
			}

			if (snekMoveCounter >= snekModifiedMocePeriod)
			{
				snekMoveCounter -= snekModifiedMocePeriod;
				const Location next = snek.GetTheHeadLocation(delta_loc);
				const Board::CellContents contents = brd.GetContents(next);
				if (!brd.IsInTheBoard(next) || snek.SnakeInItself(next) || contents == Board::CellContents::Obstacle)
				{
					gameIsOver = true;	
				}
				else if (contents == Board::CellContents::Food)
				{
					snek.Grow();
					snek.MoveBy(delta_loc);
					brd.ConsumeContents(next);
					nEatenFood++; 
					brd.SpawnContents(rng, snek, Board::CellContents::Food);
				}
				else if(contents == Board::CellContents::Poison)
				{
					snek.MoveBy(delta_loc);
					brd.ConsumeContents(next);
					if (snekMovePeriod <= snekMovePeriodMin)
					{
						snekMovePeriod = snekMovePeriodMin;
					}
					else
					{
						snekMovePeriod -= snekSpeedUpFactor;
					}
				}
				else
				{
					snek.MoveBy(delta_loc);
				}
			}
		}
	} 
	else
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameIsStarted = true;
		}
	}
}

void Game::ComposeFrame()
{

	if (!gameIsStarted)
	{
		SpriteCodex::DrawTitle(290, 220, gfx);
	}
	else
	{
		if (gameIsOver)
		{
			SpriteCodex::DrawGameOver(360, 260, gfx);
		}
		else
		{
			for (int y = 0; y < brd.GetHeight(); y++)
			{
				for (int x = 0; x < brd.GetWidth(); x++)
				{
					Location loc = { x, y };
					Color color = { 100, 100, 100 };
					brd.DrawCell(loc, color);
				}
			}

			brd.DrawCells();
			brd.DrawBorder();
			snek.Draw(brd);

		}
	}
}
