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
	s.Init();

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
	case Game::START:
		StartUpdate(delta);
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
	case Game::START:
		StartDraw(delta);
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
	int k = 0;
	for (int j = 0; j < WIN_HEIGHT; j += BOXSIZE) {
		for (int i = 0; i < WIN_WIDTH; i += BOXSIZE) {
			float ratio = j / (float)WIN_HEIGHT;
			int col = 100 + (int)(100 * ratio);
			if(k % 2)
				DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(200, 200, 200), FALSE);
			else
				DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(col,col,col), TRUE);
			k++;
		}
	}
	const int Margin = 80;
	int tSize = (std::min)(WIN_WIDTH - WIN_WIDTH%100, WIN_HEIGHT - WIN_HEIGHT % 100);
	static float dt = 0;
	float s = sin(dt);
	float st = sin(dt / 2);
	DrawExtendGraph(WIN_WIDTH/2 - tSize/2 + 50 * s, WIN_HEIGHT / 2 - tSize / 2 - Margin - 30 * st, 
		                WIN_WIDTH / 2 + tSize / 2 + 50*s, WIN_HEIGHT / 2 + tSize / 2 - Margin - 30 * st,hTitleImage, TRUE);
	SetFontSize(50);
	SetFontThickness(9);
	DrawString(303, WIN_HEIGHT / 2 + tSize / 2-97, "Push Space Key !", GetColor(0,0,0));
	DrawString(300, WIN_HEIGHT / 2 + tSize / 2 - 100, "Push Space Key !", GetColor(255, 0, 0));
	dt += delta;
}


void Game::StartUpdate(float delta)
{
	const float binterval = 0.3f;
	static float stime = 0;
	static float blinktime = 0;
	int k = 0;
	for (int j = 0; j < WIN_HEIGHT; j += BOXSIZE) {
		for (int i = 0; i < WIN_WIDTH; i += BOXSIZE) {
			float ratio = j / (float)WIN_HEIGHT;
			int col = 100 + (int)(100 * ratio);
			if (k % 2)
				DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(200, 200, 200), FALSE);
			else
				DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(col, col, col), TRUE);
			k++;
		}
	}
	const int Margin = 80;
	int tSize = (std::min)(WIN_WIDTH - WIN_WIDTH % 100, WIN_HEIGHT - WIN_HEIGHT % 100);
	static float dt = 0;
	float s = sin(dt);
	float st = sin(dt / 2);
	DrawExtendGraph(WIN_WIDTH / 2 - tSize / 2 + 50 * s, WIN_HEIGHT / 2 - tSize / 2 - Margin - 30 * st,
		WIN_WIDTH / 2 + tSize / 2 + 50 * s, WIN_HEIGHT / 2 + tSize / 2 - Margin - 30 * st, hTitleImage, TRUE);

	if (blinktime > binterval)
		blinktime = blinktime - binterval;
	float tRatio = blinktime / binterval;

	SetFontSize(50);
	SetFontThickness(9);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(tRatio*255));
	DrawString(303, WIN_HEIGHT / 2 + tSize / 2 - 97, "Push Space Key !", GetColor(0, 0, 0));
	DrawString(300, WIN_HEIGHT / 2 + tSize / 2 - 100, "Push Space Key !", GetColor(255, 0, 0));
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	blinktime += delta;
	stime += delta;
	if (stime > 2.0f)
		gs = PLAY;
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
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
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
