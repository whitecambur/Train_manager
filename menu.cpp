#include"creatmain.h"
#include"diy_level.h"
#include"playing.h"
#include"movingpic.h"
#include"button.h"
#include"draw.h"
static PIMAGE menu_background;
static PIMAGE menu_pic;
static PIMAGE menu_startpic;
static PIMAGE menu_diypic;
static PIMAGE menu_makerpic;
static PIMAGE menu_exitpic;
static PIMAGE chapter[5];
static PIMAGE menu_returnpic = NULL;
static PIMAGE menu_lastpic = NULL;
static PIMAGE menu_nextpic = NULL;
int load_menu_pic() {
	int i;
	menu_background = newimage(1000, 620);
	getimage(menu_background, "image//menu_background.png");
	menu_pic = newimage(1000, 620);
	getimage(menu_pic, "image//menu.png");
	menu_startpic = newimage(190, 270);
	getimage(menu_startpic, "image//btn_menu_start.png");
	menu_diypic = newimage(190, 270);
	getimage(menu_diypic, "image//btn_menu_diy.png");
	menu_makerpic = newimage(190, 270);
	getimage(menu_makerpic, "image//btn_menu_maker.png");
	menu_exitpic = newimage(190, 330);
	getimage(menu_exitpic, "image//btn_menu_exit.png");
	menu_lastpic = newimage(50, 150);
	getimage(menu_lastpic, "image//btn_menu_last.png");
	menu_nextpic = newimage(50, 150);
	getimage(menu_nextpic, "image//btn_menu_next.png");
	for (i = 0; i < 5; i++) {
		chapter[i] = newimage(1000, 620);
	}
	getimage(chapter[0], "image//levelback1.png");
	getimage(chapter[1], "image//levelback2.png");
	getimage(chapter[2], "image//levelback3.png");
	getimage(chapter[3], "image//levelback4.png");
	getimage(chapter[4], "image//levelbackdiy.png");
	menu_returnpic = newimage(200, 210);
	getimage(menu_returnpic, "image//menu_return.png");
	for (i = 0; i < 5; i++) {
		putimage_transparent(chapter[i], menu_returnpic, 250, 500, BLACK, 0, 0, 200, 70);
	}
	return 0;
}
int in_menu() {
	PIMAGE page = newimage(1000, 620);
	setbkcolor(RED,page);
	setfont(30, 0, "黑体", page);
	setcolor(BLACK, page);
	setbkmode(TRANSPARENT, page);
	settextjustify(CENTER_TEXT, CENTER_TEXT, page);

	button start, exit;
	button menu_diy,look_maker;
	button last, next;
	button return_menu, go_levelmaker;
	button level[15];
	mouse_msg mymouse = { 0 };
	int run = 1;													//程序运行标记
	int the_chapter = 0;											//当前章节
	int num = 0;													//关卡编号
	int change_mark = 1;											//用户diy关卡名文件是否需要重新读取
	int i = 0;														//循环变量
	start.creat(100, 360, 190, 90, menu_startpic);
	exit.creat(560, 360, 190, 110, menu_exitpic);
	menu_diy.creat(270, 360, 190, 90, menu_diypic);
	look_maker.creat(410, 360, 190, 90, menu_makerpic);
	last.creat(50, 260, 50, 50, menu_lastpic);
	next.creat(872, 260, 50, 50, menu_nextpic);
	return_menu.creat(250, 500, 200, 70, menu_returnpic);
	go_levelmaker.creat(750, 50, 190, 90, menu_diypic);
	for (i = 0; i < 15; i++) {
		level[i].creat(110 + 160 * (i % 5), 125 + 120 * (i / 5), 120, 72, NULL);
	}
	while (run==1) {
		if (mousemsg()) {
			mymouse = { 0 };
		}
		while (mousemsg()&&mymouse.is_up()==false) {
			mymouse = getmouse();
		}
		settarget(page);
		putimage(0, 0, menu_background);
		switch (the_chapter) {
		case 0:
			putimage_transparent(NULL, menu_pic, 0, 0, BLACK);
			if (start.action(mymouse) == 1) {
				mymouse = { 0 };
				for (i = 0; i < 50; i++) {
					putimage(0, 0, menu_background);
					putimage_transparent(NULL, menu_pic, -20*i, 0, BLACK);
					putimage_transparent(NULL, chapter[0], 1000 - 20 * i, 0, BLACK);
					settarget(NULL);
					putimage(0, 0, page);
					settarget(page);
					ege::Sleep(10);
				}
				the_chapter++;
			}
			if (menu_diy.action(mymouse) == 1) {
				mymouse = { 0 };
				settarget(NULL);
				blackpage(NULL);
				creatmain();
				blackpage(page);
				settarget(page);
			}
			if (look_maker.action(mymouse) == 1) {
				mymouse = { 0 };
				run = 2;
			}
			if (exit.action(mymouse) == 1) {
				mymouse = { 0 };
				run = 0;
			}
			break;
		case 1:case 2:case 3:case 4:
			putimage_transparent(NULL, chapter[the_chapter - 1], 0, 0, BLACK);
			for (i = 0; i < 15; i++) {
				if (level[i].action(mymouse) == 1) {
					mymouse = { 0 };
					num = 15 * (the_chapter - 1) + i + 1;
					settarget(NULL);
					blackpage(NULL);									//黑幕淡出
					while (num > 0 && num < 61) {
						char ch[30] = "";							//储存关卡名称
						int nextstep = 0;							//关卡完成的下一步
						sprintf(ch, "level//game_%d.txt", num);
						nextstep = in_game(ch);
						switch (nextstep) {
						case 0:num = 0; break;						//返回关卡选择界面
						case 1:break;								//重玩关卡
						case 2:num = num + 1; break;				//进入下一关
						}
					}
					if (num == 61) {
						/*完成所有关卡，给玩家一个鼓励*/
					}

					blackpage(page);
					putimage(0, 0, page);
					settarget(page);
				}
			}
			if (the_chapter != 1) {
				if (last.action(mymouse) == 1) {
					mymouse = { 0 };
					for (i = 0; i < 50; i++) {
						putimage(0, 0, menu_background);
						putimage_transparent(NULL, chapter[the_chapter - 1], 20 * i, 0, BLACK);
						putimage_transparent(NULL, chapter[the_chapter - 2], -1000 + 20 * i, 0, BLACK);
						settarget(NULL);
						putimage(0, 0, page);
						settarget(page);
						ege::Sleep(10);
					}
					the_chapter--;
				}
			}
			if (next.action(mymouse) == 1) {
				mymouse = { 0 };
				for (i = 0; i < 50; i++) {
					putimage(0, 0, menu_background);
					putimage_transparent(NULL, chapter[the_chapter - 1], - 20 * i, 0, BLACK);
					putimage_transparent(NULL, chapter[the_chapter], 1000 - 20 * i, 0, BLACK);
					settarget(NULL);
					putimage(0, 0, page);
					settarget(page);
					ege::Sleep(10);
				}
				the_chapter++;
			}
			if (return_menu.action(mymouse) == 1) {
				mymouse = { 0 };
				for (i = 0; i < 50; i++) {
					putimage(0, 0, menu_background);
					putimage_transparent(NULL, chapter[the_chapter - 1], 20 * i, 0, BLACK);
					putimage_transparent(NULL, menu_pic, -1000 + 20 * i, 0, BLACK);
					settarget(NULL);
					putimage(0, 0, page);
					settarget(page);
					ege::Sleep(10);
				}
				the_chapter = 0;
			}
			break;
		case 5:
			putimage_transparent(NULL, chapter[4], 0, 0, BLACK);
			{
				char diy_level_name[30] = "";
				get_diy_level(mymouse,diy_level_name, change_mark);				//获取关卡名
				change_mark = 0;										//已完成经改变的关卡名的读取
				if (diy_level_name[0] != '\0') {
					settarget(NULL);
					blackpage(NULL);									//黑幕淡出
					int nextstep = 1;									//关卡完成的下一步
					while (nextstep == 1) {
						nextstep = in_game(diy_level_name);
						switch (nextstep) {
						case 0:nextstep = 0; break;						//返回关卡选择界面
						case 1:nextstep = 1; break;							//重玩关卡
						case 2:nextstep = 0; break;					//返回关卡选择界面
						}
					}
					diy_level_name[0] = 0;
					blackpage(page);
					putimage(0, 0, page);
					settarget(page);
				}
			}
			if (last.action(mymouse) == 1) {
				mymouse = { 0 };
				for (i = 0; i < 50; i++) {
					putimage(0, 0, menu_background);
					putimage_transparent(NULL, chapter[4], 20 * i, 0, BLACK);
					putimage_transparent(NULL, chapter[3], -1000 + 20 * i, 0, BLACK);
					settarget(NULL);
					putimage(0, 0, page);
					settarget(page);
					ege::Sleep(10);
				}
				the_chapter--;
			}
			if (go_levelmaker.action(mymouse) == 1) {
				mymouse = { 0 };
				settarget(NULL);
				blackpage(NULL);
				creatmain();
				change_mark = 1;										//diy关卡文件名发生改变
				blackpage(page);
				settarget(page);
			}
			if (return_menu.action(mymouse) == 1) {
				mymouse = { 0 };
				for (i = 0; i < 50; i++) {
					putimage(0, 0, menu_background);
					putimage_transparent(NULL, chapter[4], 20 * i, 0, BLACK);
					putimage_transparent(NULL, menu_pic, -1000 + 20 * i, 0, BLACK);
					settarget(NULL);
					putimage(0, 0, page);
					settarget(page);
					ege::Sleep(10);
				}
				the_chapter = 0;
			}
			break;
		}
		settarget(NULL);
		putimage(0, 0, page);
		ege::Sleep(30);
	}
	start.del_btn(), exit.del_btn();
	last.del_btn(), next.del_btn();
	return_menu.del_btn(), go_levelmaker.del_btn();
	menu_diy.del_btn(); look_maker.del_btn();
	for (i = 0; i < 15; i++) {
		level[i].del_btn();
	}
	delimage(page);
	return run;
}
int look_creator() {
	return 1;
}