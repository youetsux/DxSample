#pragma once
#include <vector>
#include "globals.h"
#include "Fluits.h"
#include "Snake.h"


//class Snake;
//class Fluits;

class Game
{
	enum GAMESTATE
	{
		TITLE, START, PLAY, GAMEOVER, MAXSTATE
	};
	GAMESTATE gs;
	std::vector<pos> StageDat_;
	Snake snake;
	Fluits fluits;
public:
	int score;
	Game();
	~Game();
	void Init();
	void Update(float delta);
	void Draw(float delta);
	//Title画面用
	void TitleUpdate(float delta);
	void TitleDraw(float delta);
	//START画面=タイトルからシーン遷移してゲーム始まるまでのカウントダウン
	void StartUpdate(float delta);
	void StartDraw(float delta);
	//Play画面用
	void PlayUpdate(float delta);
	void PlayDraw(float delta);
	void DrawStage(float delta);
	//GameOver画面用
	void GameOverUpdate(float delta);
	void GameOverDraw(float delta);
};

