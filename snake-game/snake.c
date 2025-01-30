#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	WINDOW* w = initscr();
	keypad(w, true);
	nodelay(w, true);
	int posX = 0;
	int posY = 0;
	int foodX = rand() % 20;
	int foodY = rand() % 20;
	int dirX = 1;
	int dirY = 0;
	while (true) {
		int key = wgetch(w);
		if (key == KEY_LEFT) {
			dirX = -1;
			dirY = 0;
		}
		if (key == KEY_RIGHT) {
			dirX = 1;
			dirY = 0;
		}
		if (key == KEY_UP) {
			dirX = 0;
			dirY = -1;
		}
		if (key == KEY_DOWN) {
			dirX = 0;
			dirY = 1;
		}
		posX += dirX;
		posY += dirY;
		erase();
		mvaddstr(posY, posX, "*");
		mvaddstr(foodY, foodX, "&");
		if (foodX == posX && foodY == posY) {
			foodX = rand() % 20;
			foodY = rand() % 20;
		}
		usleep(100000);
	}
	endwin();
	return 0;
}
