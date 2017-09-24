#include"movingpic.h"
#include"draw.h"
static PIMAGE black;
static PIMAGE crashpic[8] = { NULL };
static PIMAGE outwaypic[8] = { NULL };
static PIMAGE wrongouterpic[8] = { NULL };
int load_movingpic() {
	int i;
	char picname[30]="";
	black = newimage(1000, 620);
	for (i = 0; i < 8; i++) {
		sprintf(picname, "image//crash_%d.png", i + 1);
		crashpic[i] = newimage(80, 80);
		getimage(crashpic[i], picname);

		sprintf(picname, "image//outway_%d.png", i + 1);
		outwaypic[i] = newimage(80, 80);
		getimage(outwaypic[i], picname);

		sprintf(picname, "image//wrongouter_%d.png", i + 1);
		wrongouterpic[i] = newimage(80, 80);
		getimage(wrongouterpic[i], picname);
	}
	return 0;
}
void blackpage(PIMAGE pimg, int depth) {
	int i = 0;
	PIMAGE page;
	if (pimg == NULL) {
		page = black;
	}
	else {
		page = pimg;
	}
	for (i = 0; i < depth; i++) {
		putimage_alphablend(NULL, page, 0, 0, 40);
		ege::Sleep(20);
	}
}
void crash(int x,int y) {
	for (int i = 0; i < 8; i++) {
		putimage_transparent(NULL, crashpic[i], 50 * x + 225, 50 * y + 5, BLACK);
		ege::Sleep(60);
	}
}
void outway(int x,int y) {
	for (int i = 0; i < 8; i++) {
		putimage_transparent(NULL, outwaypic[i], 50 * x + 225, 50 * y + 5, BLACK);
		ege::Sleep(60);
	}
}
void wrongouter(int x,int y,int num) {
	for (int i = 0; i < 8; i++) {
		putimage_transparent(NULL, wrongouterpic[i], 50 * x + 225, 50 * y + 5, BLACK);
		setcolor(GREEN);
		xyprintf(50 * x + 175, 50 * y + 45, "%d", num);
		setcolor(BLACK);
		ege::Sleep(60);
	}
}