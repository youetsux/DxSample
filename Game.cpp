#include <DxLib.h>
#include <algorithm>	
#include "Game.h"
#include "Input.h"
#include "globals.h"
#include "Snake.h"
#include "Fluits.h"


namespace
{
	Snake s;
	Fluits f;
	int hTitleImage = -1;
}


Game::Game()
{
	
}

Game::~Game()
{
}

void Game::Init()
{
	hTitleImage = LoadGraph("Image\\Title.png");
	gs = TITLE;
	f.Init();
}

void Game::Update(float delta)
{
	switch (gs)
	{
	case Game::TITLE:
		TitleUpdate(delta);
		break;
	case Game::PLAY:
		PlayUpdate(delta);
		break;
	case Game::GAMEOVER:
		GameOverUpdate(delta);
		break;
	default:
		break;
	}
}

void Game::Draw(float delta)
{
	switch (gs)
	{
	case Game::TITLE:
		TitleDraw(delta);
		break;
	case Game::PLAY:
		PlayDraw(delta);
		break;
	case Game::GAMEOVER:
		GameOverDraw(delta);
		break;
	default:
		break;
	}
}

void Game::TitleUpdate(float delta)
{
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		gs = START;
	}
}

void Game::TitleDraw(float delta)
{
	const int Margin = 80;
	int tSize = (std::min)(WIN_WIDTH - WIN_WIDTH%100, WIN_HEIGHT - WIN_HEIGHT % 100);
	DrawExtendGraph(WIN_WIDTH/2 - tSize/2, WIN_HEIGHT / 2 - tSize / 2 - Margin, WIN_WIDTH / 2 + tSize / 2, WIN_HEIGHT / 2 + tSize / 2 - Margin,hTitleImage, TRUE);
	SetFontSize(50);
	DrawString(300, WIN_HEIGHT / 2 + tSize / 2-100, "Push Space Key !", GetColor(255,0,0), GetColor(0,0,0));
}


void Game::StartUpdate(float delta)
{
}

void Game::StartDraw(float delta)
{
}

void Game::PlayUpdate(float delta)
{
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		f.Eat();
		s.Eat();
	}
	f.Update();
	s.Update(delta);
}

void Game::PlayDraw(float delta)
{
	DrawStage(delta);
	f.Draw();
	s.Draw();
}

void Game::DrawStage(float delta)
{
	//Stage
	for (int j = 0; j < WIN_HEIGHT; j += BOXSIZE) {
		for (int i = 0; i < WIN_WIDTH; i += BOXSIZE) {
			DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(200, 200, 200), FALSE);
		}
	}
}

void Game::GameOverUpdate(float delta)
{
}

void Game::GameOverDraw(float delta)
{
}
