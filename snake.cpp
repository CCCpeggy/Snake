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
	cout << "  ";
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
	for (int i = 0; i <= 6; i += 2) pushStart(start + i, end);
	newBlock();
}

Snake::~Snake()
{
	clear();
}

bool Snake::move(int direction)
{
	if (direction == NONE) direction = pForword;
	else pForword = direction;
	pair<int, int> start = snake.back();
	int x = start.first, y = start.second;
	if (direction == UP) y--;
	else if (direction == DOWN) y++;
	else if (direction == LEFT) x-=2;
	else if (direction == RIGHT) x+=2;

	x += width; x %= width;
	y += height; y %= height;

	if (touchSnake(x, y, false, false)) return false;
	pushStart(x, y);
	if (x != blockX || y != blockY) popEnd();
	else {
		newBlock();
	}

	return true;
}

bool Snake::moveValiad(int direction)
{
	int diff = direction - pForword;
	if (direction / 2 == pForword / 2 && direction % 2 != pForword % 2) return false;
	return true;
}

int Snake::getDirection() {
	while (true) {
		int key = _getch();
		switch (key) {
		case 224:
			key = _getch();
			int direction = Snake::NONE;
			switch (key)
			{
			case 0x48:
				direction = Snake::UP;
				break;
			case 0x50: 
				direction = Snake::DOWN;
				break;
			case 0x4D: 
				direction = Snake::RIGHT;
				break;
			case 0x4B: 
				direction = Snake::LEFT;
				break;
			} 
			if (direction != Snake::NONE && moveValiad(direction)) return direction;
		}
	}
}