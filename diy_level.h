#pragma once
#include"draw.h"
int load_diy_menu_pic();															//��ȡͼƬ
void get_diy_level(mouse_msg&mymouse,char level_name[],int is_reload);				//��ȡ�û�ѡ��Ĺؿ���
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
	int show(mouse_msg&mymouse);									//չʾ��Ŀ������ֵ1��ʼ��0�޲�����-1ɾ��
	void save_to_file();
private:
	static int pos;
	char name[30];
	level_line* last_line;
	level_line* next_line;
};