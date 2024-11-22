#include "DxLib.h"
#include "Input.h"
#include "deque"

namespace
{
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;
	int crrTime;
	int prevTime;
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

class sbody
{
	pos spos;
	DIR fwrdDir;
public:
	sbody();
	sbody(int x, int y);
	void SetPosition(int x, int y);
	pos GetPosition();
	void SetForward(DIR dir) { fwrdDir = dir; };
	DIR GetFoward() { return fwrdDir; };
	DIR GetBakward() { return (DIR)((fwrdDir + 2) % 4); };
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
public:
	snake();
	void AddBody(DIR dir);
	void Move();
	void Update();
	void Draw();
	DIR GetFwrdDir() { body.front(); };
};

snake::snake()
{
}

void snake::AddBody(DIR dir)
{
	DIR topDir = body.front().GetFoward();
	body.push_front({});
}

void snake::Move()
{
}

void snake::Update()
{
}

void snake::Draw()
{
}




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


	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();
		//ここにやりたい処理を書く
		crrTime = GetNowCount();
		float deltaTime = (crrTime - prevTime) / 1000.0;//フレーム間時間（ｓ）
		




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
}

void Draw(float dTime)
{
}

