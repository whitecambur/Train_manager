#include"loading.h"
#include"menu.h"
#include"draw.h"
int main() {
	setinitmode(0);
	initgraph(1000, 620);
	setfont(30, 0, "ËÎÌו");
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setbkmode(TRANSPARENT);
	load_datas();
	int run = 1, flag = 0;
	while (run) {
		switch (run) {
		case 1:run = in_menu(); break;
		case 2:run = look_creator(); break;
		}
	}
	closegraph();
}