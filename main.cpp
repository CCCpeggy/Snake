#include<iostream>
#include<Windows.h>
#include<future> 
#include<chrono> 
#include<conio.h>
#include"snake.h"
#include<time.h>
#include<Windows.h>
#include<random>
#include<utility>

using namespace std;
const int width = 100;
const int height = 25;
const int milliseconds = 200;
int getforward(Snake*);

int main() {
	srand(time(0));
	HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.dwSize = 1;
	lpCursor.bVisible = false;
	SetConsoleCursorInfo(handleOut, &lpCursor);

	Snake* snake = NULL;
	while (true) {
		if (snake != NULL) delete snake;
		snake = new Snake(handleOut, width, height, 0, 0);
		std::future<int> fut = async(getforward, snake);
		std::chrono::milliseconds span(milliseconds);
		while (true) {
			int forward = Snake::NONE;
			if (fut.wait_for(span) == std::future_status::ready) {
				forward = fut.get();
				fut = async(getforward, snake);
			}
			if (!snake->move(forward)) break;
		}
	}
	getchar();
}

int getforward(Snake* snake) {
	while (true) {
		int key = _getch();
		switch (key)
		{
		case 224:
			key = _getch();
			int forward = Snake::NONE;
			switch (key)
			{
			case 0x48:
				forward = Snake::UP;
				break;
			case 0x50: 
				forward = Snake::DOWN;
				break;
			case 0x4D: 
				forward = Snake::RIGHT;
				break;
			case 0x4B: 
				forward = Snake::LEFT;
				break;
			} 
			if (forward != Snake::NONE && snake->moveValiad(forward))
				return forward;
		}
	}
}

