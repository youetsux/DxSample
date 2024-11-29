#include <DxLib.h>
#include "Snake.h"
#include "Input.h"
#include <string>

namespace {
	int hCountImage[4]{ -1,-1,-1,-1 };
	pos dirs[] = { {0,-1},{-1, 0}, {0, 1}, {1, 0}, {0, 0} };
	int ReadyCount = -1;
}
Snake::Snake()
{
	for (int i = 0; i < 5; i++)
	{
		Sbody bd;
		bd.SetPosition(10 - i, 10);
		bd.SetForward(RIGHT);
		body.push_back(bd);
	}
	sstate = INIT;
	sdelta = 0;
	isAte = false;
}


void Snake::Init()
{
	hCountImage[0] = LoadGraph("Image\\go.png");
	hCountImage[1] = LoadGraph("Image\\ichi.png");
	hCountImage[2] = LoadGraph("Image\\ni.png");
	hCountImage[3] = LoadGraph("Image\\san.png");
}
//Ž©•ª‚ª“®‚¢‚½‚ ‚Æ‚É‚PŒÂ‘‚¦‚é
void Snake::AddBody(DIR dir)
{
}

void Snake::Move()
{
}

void Snake::Update(float delta)
{
	switch (sstate)
	{
	case INIT:
		InitUpdate(delta);
		break;
	case PLAY:
		PlayUpdate(delta);
		break;
	case DEATH:
		DeathUpdate(delta);
		break;
	case STOP:
		break;
	}

}

void Snake::PlayUpdate(float delta)
{

	DIR inputDir = NONE;
	if (Input::IsKeyDown(KEY_INPUT_UP))
	{
		inputDir = UP;
	}
	if (Input::IsKeyDown(KEY_INPUT_LEFT))
	{
		inputDir = LEFT;
	}
	if (Input::IsKeyDown(KEY_INPUT_DOWN))
	{
		inputDir = DOWN;
	}
	if (Input::IsKeyDown(KEY_INPUT_RIGHT))
	{
		inputDir = RIGHT;
	}
	Sbody& b = body.front();
	if (inputDir != b.GetBakward())
		b.SetForward(inputDir);

	const float refreshRate = 0.2f;
	//‚Ö‚Ñ‚ð‘O‚Éi‚ß‚é
	if (sdelta > refreshRate)
	{
		Sbody b = body.back();
		pos p = b.GetPosition();
		DIR d = body.front().GetFoward();
		pos fpos = body.front().GetPosition();
		pos nextPos = { fpos.x + dirs[d].x, fpos.y + dirs[d].y };
		for (int i = 1; i < body.size(); i++)
		{
			pos iPos = body.at(i).GetPosition();
			if (iPos.x == nextPos.x && iPos.y == nextPos.y)
			{
				sstate = DEATH;
				sdelta = 0;
			}
		}
		b.SetPosition(nextPos.x, nextPos.y);
		b.SetForward(d);
		body.push_front(b);
		if (!isAte) {
			body.pop_back();
		}
		else
		{
			isAte = false;
		}
		sdelta = sdelta - refreshRate;
	}


	sdelta = sdelta + delta;
}

void Snake::DeathUpdate(float delta)
{
	if (sdelta < 1.5f)
	{

		static float blink = 0;
		if (blink > 0.2f)
		{
			blink = 0;
			deathBlend = !deathBlend;
		}
		blink = blink + delta;
		sdelta = sdelta + delta;
	}
	else if (sdelta < 5.0f)
	{
		deathBlend = false;
		for (int i = 0; i < body.size(); i++)
		{
			pos p = body.at(i).GetPosition();
			pos np = { p.x + dirs[(int)(i % 4)].x, p.y + dirs[(int)(i % 4)].y };
			body.at(i).SetPosition(np.x, np.y);
		}
		sdelta = sdelta + delta;
	}
	else
	{
		sstate = STOP;
	}
}
//Draw‚ÆUpdate‚²‚Á‚¿‚á‚É‚È‚Á‚Ä‚é
void Snake::InitUpdate(float delta)
{
	static float cdtimer = 4.0f;
	if (sstate == STOP)
		return;
	
	if (cdtimer > 0)
	{
		ReadyCount = (int)cdtimer;
		cdtimer = cdtimer - delta;
	}
	else
	{
		sstate = PLAY;
	}
}

void Snake::Draw(float delta)
{
	switch (sstate)
	{
	case INIT:
		InitDraw(delta);
		break;
	case PLAY:
		PlayDraw(delta);
		break;
	case DEATH:
		DeathDraw(delta);
		break;
	case STOP:
		break;
	}

}

void Snake::PlayDraw(float delta)
{
	if (sstate == STOP)
		return;
	for (auto& itr : body)
	{
		pos p = itr.GetPosition();
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 255, 0), TRUE);
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 0, 255), FALSE);
		//DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
	}
}

void Snake::DeathDraw(float delta)
{
	if (sstate == STOP)
		return;
	for (auto& itr : body)
	{
		pos p = itr.GetPosition();
		if (!deathBlend)
			DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 255, 0), TRUE);
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 0, 255), FALSE);
		//DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
	}
}

void Snake::InitDraw(float delta)
{
	for (auto& itr : body)
	{
		pos p = itr.GetPosition();

		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 255, 0), TRUE);
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 0, 255), FALSE);
		//DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
				//std::string mess[4] = { "GO!","1","2","3" };

		//DrawFormatString(WIN_WIDTH / 2, WIN_HEIGHT / 2, GetColor(255, 0, 0), "%s", mess[(int)cdtimer].c_str());

	}
	const int numw = 150;
	const int numh = 200;
	DrawExtendGraph(WIN_WIDTH / 2 - numw / 2, WIN_HEIGHT / 2 - numh / 2,
					WIN_WIDTH / 2 + numw / 2, WIN_HEIGHT / 2 + numh / 2, hCountImage[ReadyCount], TRUE);
}
