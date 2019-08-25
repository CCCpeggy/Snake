#pragma once
#include<deque>
#include<Windows.h>
#include<iostream>
#include<random>
using namespace std;
class Snake
{
	const unsigned int WHITE = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;
	const unsigned int BLACK = 0;
	const int width, height;
	int blockX, blockY;
	HANDLE handleOut;
	int pForword = RIGHT;
	void pushStart(int, int);
	void popEnd();
	void clear();
	void drawBlock(int, int, bool);
	void newBlock();
	bool touchSnake(int, int, bool=true, bool=true);
public:
	static const int UP;
	static const int DOWN;
	static const int LEFT;
	static const int RIGHT;
	static const int NONE;

	Snake(HANDLE, int, int, int, int);
	~Snake();
	
	deque<pair<int, int>> snake;

	bool move(int = NONE);
	bool moveValiad(int);
};

