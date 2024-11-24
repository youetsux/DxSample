#include "DxLib.h"
#include "Input.h"
#include "deque"

class snake;

namespace
{
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;
	int crrTime;
	int prevTime;
	float deltaTime;

	int BOXSIZE{ 30 };
	snake* s;
}

enum DIR
{
	UP, LEFT, DOWN, RIGHT, NONE, MAXDIR
};


struct pos
{
	int x;
	int y;
};

pos dirs[] = { {0,-1},{-1, 0}, {0, 1}, {1, 0}, {0, 0} };


class sbody
{
	pos spos;
	DIR fwrdDir;
public:
	sbody();
	sbody(int x, int y);
	void SetPosition(int x, int y);
	pos GetPosition();
	void SetForward(DIR dir) { fwrdDir = dir; }
	DIR GetFoward() { return fwrdDir; }
	DIR GetBakward() { return (DIR)((fwrdDir + 2) % 4); }
};

sbody::sbody()
{
	spos = { 0, 0 };
}

sbody::sbody(int x, int y)
{
	spos = { x, y };
}

void sbody::SetPosition(int x, int y)
{
	spos = { x, y };
}

pos sbody::GetPosition()
{
	return spos;
}

class snake
{
	std::deque<sbody> body;
	enum
	{
		INIT, PLAY, MOVE, STOP, DEATH, MAXSSTATE
	}sstate;
	float sdelta;//蛇のΔt
	bool isEate;
public:
	snake();
	void AddBody(DIR dir);
	void Move();
	void Update(float delta);
	void Draw();
	DIR GetFwrdDir() { body.front().GetFoward(); };
};

snake::snake()
{
	for (int i = 0; i < 5; i++)
	{
		sbody bd;
		bd.SetPosition(10 - i, 10);
		bd.SetForward(RIGHT);
		body.push_back(bd);
	}
	sstate = INIT;
	sdelta = 0;
	isEate = false;
}

//自分が動いたあとに１個増える
void snake::AddBody(DIR dir)
{
	//DIR addDir = body.back().GetBakward();
	//DIR tailDir = body.back().GetFoward();
	//pos tailPos = body.back().GetPosition();
	//pos addPos = { tailPos.x + dirs[dir].x, tailPos.y + dirs[dir].y };
	//sbody newBody(addPos.x, addPos.y);
	//body.push_back(newBody);
}

void snake::Move()
{
}

void snake::Update(float delta)
{
	const float refreshRate = 0.3f;
	//へびを前に進める
	if (sdelta > refreshRate)
	{
		sbody b = body.back();
		pos p = b.GetPosition();
		DIR d = body.front().GetFoward();
		pos fpos = body.front().GetPosition();
		b.SetPosition(fpos.x + dirs[d].x, fpos.y + dirs[d].y);
		b.SetForward(d);
		body.push_front(b);
		if (!isEate) {
			body.pop_back();
		}
		else
		{
			isEate = false;
		}
		sdelta = sdelta - refreshRate;
	}

	if (Input::IsKeyDown(KEY_INPUT_UP))
	{
		sbody &b = body.front();
		b.SetForward(UP);
	}
	if (Input::IsKeyDown(KEY_INPUT_LEFT))
	{
		sbody &b = body.front();
		b.SetForward(LEFT);
	}
	if (Input::IsKeyDown(KEY_INPUT_DOWN))
	{
		sbody &b = body.front();
		b.SetForward(DOWN);
	}
	if (Input::IsKeyDown(KEY_INPUT_RIGHT))
	{
		sbody &b = body.front();
		b.SetForward(RIGHT);
	}
	if (Input::IsKeyDown(KEY_INPUT_SPACE))
	{
		isEate = true;
	}

	sdelta = sdelta + delta;
}

void snake::Draw()
{
	for (auto& itr : body)
	{
		pos p = itr.GetPosition();
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 255, 0), TRUE);
		DrawBox(p.x * BOXSIZE, p.y * BOXSIZE, (p.x + 1) * BOXSIZE, (p.y + 1) * BOXSIZE, GetColor(0, 0, 255), FALSE);
		DrawFormatString(20, 80, GetColor(0, 0, 0), "%d", isEate);
	}
}


enum TYPE_FLUItS
{
	APPLE,
	STRAWBERRY,
	BANANA,
	MELON,
	MAX_FLUITS
};
class fruits
{
	pos position;
	int kind;//フルーツの種類
};


void Init();
void Update(float dTime);
void Draw(float dTime);

void DxInit()
{
	ChangeWindowMode(true);
	SetWindowSizeChangeEnableFlag(false, false);
	SetMainWindowText("TITLE");
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
	SetWindowSizeExtendRate(1.0);
	SetBackgroundColor(255, 250, 205);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		DxLib_End();
	}

	SetDrawScreen(DX_SCREEN_BACK);
}

void MyGame()
{

	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
	static int timer = 0;
	timer++;
	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	s = new snake();
	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();
		//ここにやりたい処理を書く
		crrTime = GetNowCount();
		deltaTime = (float)(crrTime - prevTime) / 1000.0;//フレーム間時間（ｓ）

		Init();
		Update(deltaTime);
		Draw(deltaTime);

		DrawFormatString(20, 50, GetColor(0, 0, 0), "%lf", deltaTime);
		ScreenFlip();
		WaitTimer(16);

		prevTime = crrTime;
		if (ProcessMessage() == -1)
			break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)
			break;
	}

	DxLib_End();
	return 0;
}

void Init()
{
}

void Update(float dTime)
{
	s->Update(dTime);
}

void Draw(float dTime)
{
	//Stage
	for (int j = 0; j < WIN_HEIGHT; j += BOXSIZE) {
		for (int i = 0; i < WIN_WIDTH; i += BOXSIZE) {
			DrawBox(i, j, i + BOXSIZE, j + BOXSIZE, GetColor(200, 200, 200), FALSE);
		}

	}
	s->Draw();
}

