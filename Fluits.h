#pragma once
#include <vector>
#include <DxLib.h>
#include "globals.h"

class Fluits
{
	enum FLUIT_TYPE
	{
		APPLE,
		STRAWBERRY,
		BANANA,
		MELON,
		MAX_FLUITS
	};
	std::vector<unsigned int> fcolor;
	//{ GetColor(255, 50, 50), GetColor(187, 85, 97), GetColor(255, 225, 53), GetColor(224, 222, 148) };
public:
	Fluits();
	~Fluits();
	pos position;
	FLUIT_TYPE type;
	int color;
	void SetType();
	void SetPosition(int x, int y); 
	bool isActive;
	void SetFluits();
	void Eat(); 
	void Init(); 
	void Update();
	void Draw();
};

