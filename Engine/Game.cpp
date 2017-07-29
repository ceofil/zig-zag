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
#include <fstream>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Graphics::GetCenter(), 110.0f),
	path(score, highScore, 110.0f, Vec2(2.0f,-1.0f)),
	txt(gfx,0,0,2,2,1000,1000)
{
	LoadHighScore();
}

Game::~Game()
{
	SaveHighScore();
}

void Game::Go()
{
	gfx.BeginFrame();

	float timeperiod = ft.Mark();
	while (timeperiod > 0.0f)
	{
		const float dt = std::min(0.0025f, timeperiod);
		UpdateModel(dt);
		timeperiod -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	//ball.Update(wnd.kbd, dt);
	//path.Update(dt); 
	if (path.ContainsBall(ball.GetX()) == false)
	{
		score = 0;
	}
}


void Game::ComposeFrame()
{
	path.Draw(gfx);
	ball.Draw(gfx);
	txt.drawint(score, 75, 290, Colors::Red);
	txt.drawint(highScore, 150, 290, Colors::LightGray);

	//grid
	//gfx.DrawHorizontalLine(300, 0, 399, Colors::Red);
	//gfx.DrawVerticalLine(200, 0, 599, Colors::Red);

}

void Game::LoadHighScore()
{
	std::ifstream in("hs.txt");
	in >> highScore;
}

void Game::SaveHighScore()
{
	std::ofstream out("hs.txt");
	out << highScore;
}