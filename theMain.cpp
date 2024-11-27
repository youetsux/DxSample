#include "DxLib.h"
#include "Input.h"
#include "globals.h"
#include "deque"
#include <vector>
#include "Snake.h"
#include "Fluits.h"
#include "Game.h"


namespace
{
	Game MyGame;
}

//void Init();
//void Update(float dTime);
//void Draw(float dTime);

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

//void MyGame()
//{
//
//	DrawFormatString(100, 100, GetColor(0, 0, 0), "ウィンドウのテスト");
//	static int timer = 0;
//	timer++;
//	DrawFormatString(100, 150, GetColor(0, 0, 0), "%010d", timer);
//}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	DxInit();
	crrTime = GetNowCount();
	prevTime = GetNowCount();

	//s = new snake();
	MyGame.Init();
	while (true)
	{
		ClearDrawScreen();
		Input::KeyStateUpdate();
		//ここにやりたい処理を書く
		crrTime = GetNowCount();
		deltaTime = (float)(crrTime - prevTime) / 1000.0;//フレーム間時間（ｓ）

	
		MyGame.Update(deltaTime);
		MyGame.Draw(deltaTime);

		//DrawFormatString(20, 50, GetColor(0, 0, 0), "%lf", deltaTime);
		//DrawFormatString(20, 130, GetColor(0, 0, 0), "%4d, %4d", STAGEW, STAGEH);
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

//void Init()
//{
//	
//}
//
//void Update(float dTime)
//{
//
//}
//
//void Draw(float dTime)
//{
//
//}

