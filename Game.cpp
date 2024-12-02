#include <DxLib.h>
#include <algorithm>	
#include "Game.h"
#include "Input.h"
#include "globals.h"
#include "Snake.h"
#include "Fluits.h"
#include "easingfunc.h"


namespace
{
	Snake s;
	Fluits f;
	int hTitleImage = -1;
	float startTimer = 0;
	float stime = 0;
	float sBlinkTimer = 0;
	int hGameOverImage = -1;
	int hiScore = 0;
	int lastScore = 0;
	int CurrentScore = 0;
	int gameNum = 0;
}


Game::Game()
{

}

Game::~Game()
{
}

void Game::Init()
{
	if(hTitleImage < 0)
		hTitleImage = LoadGraph("Image\\Title.png");
	if (hGameOverImage < 0)
		hGameOverImage = LoadGraph("Image\\gameover.png");
	s.Init();

	StageDat_.clear();//壁のデータだけ入れる（1年生には、全部のデータを配列にした方がわかりやすいかも
	for (int j = 0; j < STAGEH; j++)
	{
		for (int i = 0; i < STAGEW; i++)
		{

			if (j == 0 || i == 0 || j == STAGEH - 1 || i == STAGEW - 1)
			{
				pos p{ i, j };
				StageDat_.push_back(p);
			}
		}
	}
	gs = TITLE;
	f.Init();
	score = 0;
	stime = 0;

	gameNum++;
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
		s.Init();
		f.Init();
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
			if (k % 2)
				DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(200, 200, 200), FALSE);
			else
				DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(col, col, col), TRUE);
			k++;
		}
	}
	const int Margin = 80;
	int tSize = (std::min)(WIN_WIDTH - WIN_WIDTH % 100, WIN_HEIGHT - WIN_HEIGHT % 100);
	//static float dt = 0;
	float dt = GetNowCount() / 1000.0f;
	float s = sin(dt);
	float st = sin(dt / 2);
	DrawExtendGraph(WIN_WIDTH / 2 - tSize / 2 + 50 * s, WIN_HEIGHT / 2 - tSize / 2 - Margin - 30 * st,
		WIN_WIDTH / 2 + tSize / 2 + 50 * s, WIN_HEIGHT / 2 + tSize / 2 - Margin - 30 * st, hTitleImage, TRUE);
	SetFontSize(50);
	SetFontThickness(9);
	DrawString(303, WIN_HEIGHT / 2 + tSize / 2 - 97, "Push Space Key !", GetColor(0, 0, 0));
	DrawString(300, WIN_HEIGHT / 2 + tSize / 2 - 100, "Push Space Key !", GetColor(255, 0, 0));
	dt += delta;
}


void Game::StartUpdate(float delta)
{
	const float binterval = 0.3f;
	//static float stime = 0;
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
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(tRatio * 255));
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

	f.Update();
	s.Update(delta);
	for (auto itr : StageDat_)
	{
		pos spos = s.GetHeadPos();
		if (spos.x == itr.x && spos.y == itr.y)
		{
			s.SetDeathState();
		}
	}
	if (f.position.x == s.GetHeadPos().x && f.position.y == s.GetHeadPos().y)
	{
		score++;
		f.Eat();
		s.Eat();
		
		while(s.IsCrossBody(f.position))
		{
			f.SetFluits();
		}

	}
	if (s.IsDead())
	{
		gs = GAMEOVER;
	}
}

void Game::PlayDraw(float delta)
{
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawStage(delta);
	f.Draw();
	s.Draw(delta);

}

void Game::DrawStage(float delta)
{
	//Draw Grid
	int n = 0;
	bool rFlag = false;
	//pos MGN{ STAGEMGN_W * BOXSIZE,STAGEMGN_H * BOXSIZE };
	for (int j = 0; j < STAGEH; j++)
	{
		for (int i = 0; i < STAGEW; i++)
		{
			pos p1 = { i * BOXSIZE + DRAWMGN_W, j * BOXSIZE + DRAWMGN_H };
			pos p2 = { (i + 1) * BOXSIZE + DRAWMGN_W, (j + 1) * BOXSIZE + DRAWMGN_H };
			if ((i + (int)rFlag) % 2 == 0)
				DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(230, 230, 250), TRUE);
			else
				DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(240, 248, 255), TRUE);
		}
		rFlag = !rFlag;
	}
	//Draw Walls
	for (auto itr : StageDat_)
	{
		pos p1 = { itr.x * BOXSIZE + DRAWMGN_W, itr.y * BOXSIZE + DRAWMGN_H };
		pos p2 = { (itr.x + 1) * BOXSIZE + DRAWMGN_W, (itr.y + 1) * BOXSIZE + DRAWMGN_H };
		DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(181, 82, 51), TRUE);
		DrawBox(p1.x, p1.y, p2.x, p2.y, GetColor(0, 0, 0), FALSE);
	}
	SetFontSize(30);
	DrawFormatString(600, 80, GetColor(0,0,0),"CURRENT SCORE %03d", score);
	ChangeFontType(DX_FONTTYPE_EDGE);
	DrawFormatString(200, 40, GetColor(255, 0, 0), "  HI SCORE %03d", hiScore);
	DrawFormatString(200, 80, GetColor(255, 0, 0), "LAST SCORE %03d", lastScore);
	ChangeFontType(DX_FONTTYPE_NORMAL);
}

void Game::GameOverUpdate(float delta)
{

	if (score > hiScore)
		hiScore = score;
	if (CheckHitKeyAll())
	{
		if (gameNum > 0)
			lastScore = score;
		gs = TITLE;
		Init();
	}

}

void Game::GameOverDraw(float delta)
{
	static float dt = 0.0f;
	const float extime = 2.0f;
	const int HMGN{ 100 };
	float maxSize = 500;
	float fixtime = 0;
	const int col[] = { GetColor(255,0,0),
						GetColor(255,165,0),
						GetColor(255,255,0),
						GetColor(0,128,0),
						GetColor(0,255,255),
						GetColor(0,0,255),
						GetColor(128,0,128)
	};


	float scale = Util::EaseFunc["OutBounce"](std::clamp(dt/2.0f, 0.0f, 1.0f));
	pos gsize;
	maxSize = maxSize * scale;
	GetGraphSize(hGameOverImage, &gsize.x, &gsize.y);
	pos DrawSize{ maxSize*(gsize.y / (float)gsize.x),maxSize };
	pos p = { WIN_WIDTH / 2-DrawSize.x/2, WIN_HEIGHT / 2-DrawSize.y/2 - HMGN };
	DrawExtendGraph(p.x, p.y, p.x+ maxSize, p.y+ maxSize, hGameOverImage, TRUE);


	
	SetFontSize(40);
	ChangeFontType(DX_FONTTYPE_EDGE);
	DrawFormatString(300, 600, GetColor(255, 0, 0), "     HI SCORE %03d", hiScore);
	//ChangeFontType(DX_FONTTYPE_EDGE);
	DrawFormatString(300, 650, GetColor(255, 255, 255),   "   LAST SCORE %03d", lastScore);
	//ChangeFontType(DX_FONTTYPE_EDGE);
	DrawFormatString(300, 700, GetColor(255, 255, 255),   "CURRENT SCORE %03d", score);

	//ChangeFontType(DX_FONTTYPE_NORMAL);
	if (dt > extime)
	{
		
		DrawString(300, 540, "Push Any Key to Title", GetColor(0, 255, 0),col[((int)dt)%7]);
	}
	dt = dt + delta;
}

