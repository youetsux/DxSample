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

	const int STAGEW = WIN_WIDTH / BOXSIZE;
	const int STAGEH = WIN_HEIGHT / BOXSIZE;

}

