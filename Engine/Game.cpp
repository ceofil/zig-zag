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
#include <stdio.h>

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	ball(Graphics::GetCenter(), speed),
	path(score, highScore, speed, Vec2(2.0f, -1.0f), ball),
	txt(gfx, 0, 0, 1),
	soundtrack(L"clearside.wav", 0.0f, 72.0f), // awesomeness.wav", 0.0f, 47.0f), 
	menuMusic(L"menuMusic.wav", 0.0f, 35.0f)
{
	LoadData();
	menuMusic.Play();
}

Game::~Game()
{
	SaveData();
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
	switch (state)
	{
	case GameState::firstMenu:
	{
		if (!wnd.kbd.KeyIsEmpty())
		{
			const auto e = wnd.kbd.ReadKey();
			if (e.IsPress())
			{
				gamesPlayed++;
				state = GameState::started;
				menuMusic.StopAll();
				soundtrack.Play();
			}
		}
		break;
	}
	case GameState::started:
	{
		ball.Update(wnd.kbd, dt);
		path.Update(dt);
		if (path.ContainsBall(ball.GetX()) == false)
		{
			state = GameState::died;
			soundtrack.StopAll();
			menuMusic.Play();
		}
		break;
	}
	case GameState::died:
	{
		if (!wnd.kbd.KeyIsEmpty())
		{
			const auto e = wnd.kbd.ReadKey();
			if (e.IsPress())
			{
				if(e.GetCode() == VK_RETURN)
				{
					speed = startingSpeed;
					score = 0;
					path.Reset(ball);
					state = GameState::firstMenu;
				}
			}
		}
		break;
	}
	}
}


void Game::ComposeFrame()
{
	switch (state)
	{
	case GameState::firstMenu:
	{
		path.Draw(gfx);
		ball.Draw(gfx);
		txt.drawStringSizedCenter("zigzag", xCenter, 150, 7, Colors::White);
		txt.drawStringSizedCenter("press any key to play", xCenter, Graphics::ScreenHeight / 2 - 30, 1, Color(0, 105, 195));

		sprintf(chBuffer, "best score` %i", highScore);
		txt.drawStringSizedCenter(chBuffer, xCenter, 520, 3, Colors::White);
		sprintf(chBuffer, "games played %i", gamesPlayed);
		txt.drawStringSizedCenter(chBuffer, xCenter, 550, 3, Colors::White);
		break;
	}
	case GameState::started:
	{
		path.Draw(gfx);
		ball.Draw(gfx);
		txt.drawIntSizedRight(score, Graphics::ScreenWidth - 25, 25, 3, Colors::White);
		break;
	}
	case GameState::died:
	{
		path.Draw(gfx);
		txt.drawStringSizedCenter("game over", xCenter, 150, 7, Colors::White);

		txt.drawIntSizedCenter(score, xCenter, 320, 10, Colors::White);
		sprintf(chBuffer, "best %i", highScore);
		txt.drawStringSizedCenter(chBuffer, xCenter, 520, 3, Colors::White);

		txt.drawStringSizedCenter("press enter to retry", xCenter, Graphics::ScreenHeight - 30, 1, Colors::White);
		break;
	}
	}

	//grid
	//gfx.DrawHorizontalLine(300, 0, 399, Colors::Red);
	//gfx.DrawVerticalLine(200, 0, 599, Colors::Red);

}

void Game::LoadData()
{
	std::ifstream in("hs.txt");
	in >> highScore;
	in >> gamesPlayed;
}

void Game::SaveData()
{
	std::ofstream out("hs.txt");
	out << highScore;
	out << " ";
	out << gamesPlayed;
}