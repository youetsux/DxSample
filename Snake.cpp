#include <DxLib.h>
#include "Snake.h"
#include "Input.h"


pos dirs[] = { {0,-1},{-1, 0}, {0, 1}, {1, 0}, {0, 0} };

Snake::Snake()
{
	for (int i = 0; i < 5; i++)
	{
		Sbody bd;
		bd.SetPosition(10 - i, 10);
		bd.SetForward(RIGHT);
		body.push_back(bd);
	}
	sstate = PLAY;
	sdelta = 0;
	isAte = false;
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
	const float refreshRate = 0.3f;
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

void Snake::Draw()
{
	if (sstate == STOP)
		return;
	for (auto& itr : body)
	{
		pos p = itr.GetPosition();
		if(!deathBlend)
			DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 255, 0), TRUE);
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 0, 255), FALSE);
		DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", sstate);
	}
}
