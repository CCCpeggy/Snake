#include<iostream>
#include<future> 
#include<chrono> 
#include"snake.h"
#include<time.h>
#include<Windows.h>
#include<random>
using namespace std;

const int width = 100;
const int height = 25;
const int milliseconds = 200;

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
		std::future<int> fut = async(&Snake::getDirection, snake);
		std::chrono::milliseconds span(milliseconds);
		while (true) {
			int direction = Snake::NONE;
			if (fut.wait_for(span) == std::future_status::ready) {
				direction = fut.get();
				fut = async(&Snake::getDirection, snake);
			}
			if (!snake->move(direction)) break;
		}
	}
	getchar();
}