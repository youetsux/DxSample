#pragma once

class Snake;
class Fluits;

class Game
{
	enum GAMESTATE
	{
		TITLE, START, PLAY, GAMEOVER, MAXSTATE
	};
	GAMESTATE gs;
public:
	Game();
	~Game();
	void Init();
	void Update(float delta);
	void Draw(float delta);
	//Title��ʗp
	void TitleUpdate(float delta);
	void TitleDraw(float delta);
	//START���=�^�C�g������V�[���J�ڂ��ăQ�[���n�܂�܂ł̃J�E���g�_�E��
	void StartUpdate(float delta);
	void StartDraw(float delta);
	//Play��ʗp
	void PlayUpdate(float delta);
	void PlayDraw(float delta);
	void DrawStage(float delta);
	//GameOver��ʗp
	void GameOverUpdate(float delta);
	void GameOverDraw(float delta);
};
