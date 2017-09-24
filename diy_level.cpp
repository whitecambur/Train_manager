#include<stdio.h>
#include<string.h>
#include"diy_level.h"
#include"button.h"
static level_line Head;											//储存条目
static PIMAGE btnpic_diy_up = NULL;
static PIMAGE btnpic_diy_down = NULL;
static PIMAGE btnpic_diy_del = NULL;
int level_line::pos = 0;
static int pos_num = 0;
int load_diy_menu_pic() {
	btnpic_diy_up = newimage(50, 150);
	getimage(btnpic_diy_up, "image//btn_diy_up.png");
	btnpic_diy_down = newimage(50, 150);
	getimage(btnpic_diy_down, "image//btn_diy_down.png");
	btnpic_diy_del = newimage(50, 150);
	getimage(btnpic_diy_del, "image//btn_diy_del.png");
	return 0;
}
void get_diy_level(mouse_msg&mymouse,char level_name[],int is_reload) {
	if (is_reload == 1) {
		Head.del_all();
		Head.find_diy_file();
	}
	button go_up, go_down;
	go_up.creat(850, 140, 50, 50, btnpic_diy_up);
	go_down.creat(850, 390, 50, 50, btnpic_diy_down);
	Head.clear_pos(pos_num);
	Head.show_all(mymouse,level_name);
	rectangle(100, 140, 900, 440);
	rectangle(850, 140, 900, 440);
	setfillcolor(BLACK);
	if (Head.get_pos() - pos_num <= 6) {
		bar(850, 190, 900, 390);
	}
	else {
		int cube_pos = 190 + (double(-pos_num) / double(Head.get_pos() - pos_num - 6)) * 170;
		bar(850, cube_pos, 900, cube_pos + 30);
	}
	if (Head.get_pos() < 6 && pos_num < 0) {
		pos_num++;
	}
	if (go_up.action(mymouse) == 1 || mymouse.wheel > 30) {
		mymouse = { 0 };
		if (pos_num < 0) {
			pos_num++;
		}
	}
	if (go_down.action(mymouse) == 1 || mymouse.wheel < -30) {
		mymouse = { 0 };
		if (Head.get_pos() > 6) {
			pos_num--;
		}
	}
	go_up.del_btn();
	go_down.del_btn();
}
void level_line::find_diy_file() {
	FILE*p;
	p = fopen("addons//train_manager.ll", "r");
	if (p == NULL) {
		MessageBox(NULL,TEXT("无法找到关卡名称记录文件"),TEXT("错误提醒"),MB_SETFOREGROUND);
	}
	else {
		int error = 0;
		level_line add;
		fgets(add.name, 24, p);
		if (add.name[0] != 0&& strlen(add.name)<21) {
			add.name[strlen(add.name) - 1] = 0;
		}
		while (!feof(p) && error == 0) {
			this->add_line(add);
			fgets(add.name, 24, p);
			if (add.name[0] != 0 && strlen(add.name)<21) {
				add.name[strlen(add.name) - 1] = 0;
			}
			else {
				error = 1;
			}
		}
		if (error == 1) {
			MessageBox(NULL, TEXT("关卡名称记录文件异常"), TEXT("错误提醒"), MB_SETFOREGROUND);
		}
		fclose(p);
	}
}
void level_line::show_all(mouse_msg&mymouse, char level_name[]) {
	level_line*p = this;
	int is_change = 0;
	if (p != NULL) {
		p = p->next_line;
		while (p != NULL) {
			switch (p->show(mymouse)) {
			case 1:sprintf(level_name,"addons//%s.txt",p->name); p = p->next_line; break;
			case 0:p = p->next_line; break;
			case -1:
				level_line*killer = p;
				p = p->next_line;
				killer->del_line(1);
				delete killer;
				killer = NULL;
				is_change = 1;
				break;
			}	
		}
	}
	p = NULL;
	if (is_change == 1) {
		this->save_to_file();
	}
}
void level_line::add_line(level_line&addtion) {
	level_line*p = this;
	if (p != NULL) {
		while (p->next_line != NULL) {
			p = p->next_line;
		}
		p->next_line = new level_line;
		sprintf(p->next_line->name, "%s", addtion.name);
		p->next_line->last_line = p;
	}
	p = NULL;
}
void level_line::del_line(int flag) {
	if (flag == 1) {
		char filename[30];
		sprintf(filename, "addons//%s.txt", this->name);
		remove(filename);
		sprintf(filename, "addons//%s.lm", this->name);
		remove(filename);
	}
	if (this->next_line != NULL) {
		this->next_line->last_line = this->last_line;
	}
	if (this->last_line != NULL) {
		this->last_line->next_line = this->next_line;
	}
	this->next_line = NULL;
	this->last_line = NULL;
}
void level_line::del_all() {
	level_line *p=this;
	if (p != NULL) {
		if (p->next_line != NULL) {
			while (p->next_line != NULL) {
				p = p->next_line;
			}
			while (p != this) {
				level_line*killer = p;
				p = p->last_line;
				killer->del_line(0);
				delete killer;
				killer = NULL;
			}
		}
	}
	p = NULL;
}
int level_line::show(mouse_msg&mymouse) {
	if (pos >= 0 && pos <= 5) {
		int flag = 0;
		button seclect, del;
		seclect.creat(100, 140 + 50 * pos, 700, 50, NULL);
		del.creat(800, 140 + 50 * pos, 50, 50, btnpic_diy_del);
		setfillcolor(EGERGB(0,100,200));
		bar(100, 140 + 50 * pos, 800, 190 + 50 * pos);
		setcolor(BLACK);
		rectangle(100, 140 + 50 * pos, 800, 190 + 50 * pos);
		settextjustify(LEFT_TEXT, CENTER_TEXT);
		outtextxy(115, 165 + 50 * pos, this->name);
		if (seclect.action(mymouse)==1) {
			mymouse = { 0 };
			flag = 1;
		}
		if (del.action(mymouse) == 1) {
			mymouse = { 0 };
			flag = -1;
		}
		pos++;

		settextjustify(CENTER_LINE, CENTER_TEXT);
		seclect.del_btn();
		del.del_btn();
		return flag;
	}
	else {
		pos++;
		return 0;
	}
}
void level_line::save_to_file() {
	level_line*p = this;
	if (p != NULL) {
		FILE *f = fopen("addons//train_manager.ll", "w");
		while (p->next_line != NULL) {
			p = p->next_line;
			fputs(p->name, f);
			fputc('\n', f);
		}
		fclose(f);
	}
}