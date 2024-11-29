#pragma once

enum DIR
{
	UP, LEFT, DOWN, RIGHT, NONE, MAXDIR
};


struct pos
{
	int x;
	int y;
};

namespace
{
	const int WIN_WIDTH = 1024;
	const int WIN_HEIGHT = 768;
	int crrTime;
	int prevTime;
	float deltaTime;

	int BOXSIZE{ 30 };
	const int STAGEMGN_W = 2;
	const int STAGEMGN_H = 4;
	const int STAGEW = WIN_WIDTH / BOXSIZE - STAGEMGN_W;
	const int STAGEH = WIN_HEIGHT / BOXSIZE - STAGEMGN_H;
	const int DRAWMGN_W = STAGEMGN_W * BOXSIZE / 2;//マージンとって真ん中に描画
	const int DRAWMGN_H = STAGEMGN_H * BOXSIZE;//スコア表示のために上を開ける
}

