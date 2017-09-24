#pragma once
#include"draw.h"
int load_diy_menu_pic();															//读取图片
void get_diy_level(mouse_msg&mymouse,char level_name[],int is_reload);				//获取用户选择的关卡名
class level_line {
public:
	level_line(){
		this->name[0] = '\0';
		this->last_line = 0;
		this->next_line = 0;
	}
	static void clear_pos(int num) {
		pos = num;
	}
	static int get_pos() {
		return pos;
	}
	void find_diy_file();
	void show_all(mouse_msg&mymouse, char level_name[]);
	void add_line(level_line&addtion);
	void del_line(int flag);
	void del_all();
	int show(mouse_msg&mymouse);									//展示条目，返回值1开始，0无操作，-1删除
	void save_to_file();
private:
	static int pos;
	char name[30];
	level_line* last_line;
	level_line* next_line;
};