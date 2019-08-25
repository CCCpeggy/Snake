#include "snake.h"

const int Snake::UP = 0;
const int Snake::DOWN = 1;
const int Snake::LEFT = 2;
const int Snake::RIGHT = 3;
const int Snake::NONE = -1;

void Snake::pushStart(int x, int y)
{
	snake.push_back(pair<int, int>(x, y));
	drawBlock(x, y, true);
}

void Snake::popEnd()
{
	pair<int, int> end = snake.front();
	drawBlock(end.first, end.second, false);
	snake.pop_front();
}

void Snake::clear()
{
	SetConsoleTextAttribute(handleOut, BLACK);
	system("cls");
}

void Snake::drawBlock(int x, int y, bool visible)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleTextAttribute(handleOut, visible ? WHITE : BLACK);
	SetConsoleCursorPosition(handleOut, coord);
	cout << "¡@";
}

void Snake::newBlock()
{
	do {
		blockX = (rand() % (width / 2)) * 2;
		blockY = rand() % height;
	}while (touchSnake(blockX, blockY));
	drawBlock(blockX, blockY, true);
}

bool Snake::touchSnake(int x, int y, bool start, bool end)
{
	deque<pair<int, int> >::iterator iter = snake.begin() + (start ? 1 : 0);
	for (; (iter + (end ? 1 : 0)) != snake.end(); iter++) {
		if (iter->first == x && iter->second == y) return true;
	}
	return false;
}

Snake::Snake(HANDLE handleOut, int width, int height, int start, int end)
	:handleOut(handleOut), width(width), height(height)
{
	SetConsoleTextAttribute(handleOut, BLACK);
	int x = start;
	int y = end;
	pushStart(x, y);
	pushStart(x + 1, y);
	pushStart(x + 2, y);
	pushStart(x + 3, y);
	pushStart(x + 4, y);
	pushStart(x + 5, y);
	pushStart(x + 6, y);
	newBlock();
}

Snake::~Snake()
{
	clear();
}

bool Snake::move(int forward)
{
	if (forward == NONE) forward = pForword;
	else pForword = forward;
	pair<int, int> start = snake.back();
	int x = start.first, y = start.second;
	if (forward == UP) y--;
	else if (forward == DOWN) y++;
	else if (forward == LEFT) x-=2;
	else if (forward == RIGHT) x+=2;
	SetConsoleTextAttribute(handleOut, WHITE);

	x += width; x %= width;
	y += height; y %= height;

	if (touchSnake(x, y, false, false)) return false;

	pushStart(x, y);
	if (x != blockX || y != blockY) popEnd();
	else newBlock();

	return true;
}

bool Snake::moveValiad(int forward)
{
	SetConsoleTextAttribute(handleOut, WHITE);
	int diff = forward - pForword;
	if (forward / 2 == pForword / 2 && forward % 2 != pForword % 2) return false;
	return true;
}
