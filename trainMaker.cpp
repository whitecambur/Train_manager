#include <graphics.h>
#include "levelmaker.h"
#include "mine_btn.h"
#include "para.h"
#include "others.h"

//�ⲿ��������
void print_screen();

//ģ���ں�������
void print_screen_train();
void reset_font(PIMAGE);
static int in_control=0;

//�𳵱༭��������
void btnf_edit_train() {
	in_control=0;		//�ж����ڽ�������Ŀ�
	mouse_msg msg = {0};
	for (;1; ) {
		print_screen_train();
		while (mousemsg()) {
			msg = getmouse();

			if (msg.is_left() && msg.is_down()) { //�������
				in_control = 0;
				if (trains[ctrl.train_code - 1].length < 1) {
					trains[ctrl.train_code - 1].length = 1;
				}
				if (btn_left_a.left(msg.x, msg.y)) {
					if (ctrl.train_code > 1)
						ctrl.train_code--;
				}
				if (btn_right_a.left(msg.x, msg.y)) {
					if (ctrl.train_code < 20)
						ctrl.train_code++;
				}
				if (btn_enterxy.left(msg.x, msg.y)) {
					btn_enterxy.set_highlight(0);
				}
				if (btn_outerxy.left(msg.x, msg.y)) {
					btn_outerxy.set_highlight(0);
				}
				if (btn_showtime.left(msg.x, msg.y)) {
					in_control = 1;
					/*char temp[5];
					inputbox_getline("������", "������𳵵ĳ���ʱ�� ��Χ��1~9999", temp, 5);
					int t;
					t = to_int(temp, 4);
					if (t >= 1 && t <= 9999)
					  trains[ctrl.train_code - 1].showtime = t;
					*/
				}
				if (btn_speed.left(msg.x, msg.y)) {
					trains[ctrl.train_code - 1].speed = !trains[ctrl.train_code - 1].speed;
				}
				if (btn_length.left(msg.x, msg.y)) {
					in_control = 2;
					/*char temp[3];
					inputbox_getline("������", "������𳵵ĳ��� ��Χ��1~20", temp, 3);
					int t;
					t = to_int(temp, 2);
					if (t >= 1 && t <= 20)
					  trains[ctrl.train_code - 1].length = t;
					*/
				}
				if (btn_back.left(msg.x, msg.y)) {
					return;
				}
				msg = { 0 };
			}
			else if (msg.is_right() && msg.is_down()) { //�Ҽ�����
				if (btn_enterxy.right(msg.x, msg.y));
				if (btn_outerxy.right(msg.x, msg.y));
				in_control = 0;
				msg = { 0 };
			}
			else { //hover & hoverback
				if (btn_left_a.hover(msg.x, msg.y)) {
					btn_left_a.set_highlight(1);
				}
				if (btn_right_a.hover(msg.x, msg.y)) {
					btn_right_a.set_highlight(1);
				}
				if (btn_enterxy.hover(msg.x, msg.y)) {
					btn_enterxy.set_highlight(1);
				}
				if (btn_outerxy.hover(msg.x, msg.y)) {
					btn_outerxy.set_highlight(1);
				}
				if (btn_showtime.hover(msg.x, msg.y)) {
					btn_showtime.set_highlight(1);
				}
				if (btn_speed.hover(msg.x, msg.y)) {
					btn_speed.set_highlight(1);
				}
				if (btn_length.hover(msg.x, msg.y)) {
					btn_length.set_highlight(1);
				}
				if (btn_back.hover(msg.x, msg.y)) {
					btn_back.set_highlight(1);
				}
				if (btn_left_a.hoverback(msg.x, msg.y)) {
					btn_left_a.set_highlight(0);
				}
				if (btn_right_a.hoverback(msg.x, msg.y)) {
					btn_right_a.set_highlight(0);
				}
				if (btn_enterxy.hoverback(msg.x, msg.y)) {
					btn_enterxy.set_highlight(0);
				}
				if (btn_outerxy.hoverback(msg.x, msg.y)) {
					btn_outerxy.set_highlight(0);
				}
				if (btn_showtime.hoverback(msg.x, msg.y)) {
					btn_showtime.set_highlight(0);
				}
				if (btn_speed.hoverback(msg.x, msg.y)) {
					btn_speed.set_highlight(0);
				}
				if (btn_length.hoverback(msg.x, msg.y)) {
					btn_length.set_highlight(0);
				}
				if (btn_back.hoverback(msg.x, msg.y)) {
					btn_back.set_highlight(0);
				}
				msg = { 0 };
			}
		}
		if(in_control!=0) {
			if(ege::kbhit()) {
				int ch=ege::getch();
				switch(in_control) {
					case 1:
						if(ch>='0'&&ch<='9') {
							trains[ctrl.train_code - 1].showtime=trains[ctrl.train_code - 1].showtime*10+ch-'0';
							if(trains[ctrl.train_code - 1].showtime>999999) {
								trains[ctrl.train_code - 1].showtime=999999;
							}
						} else if(ch==8) {
							trains[ctrl.train_code - 1].showtime=trains[ctrl.train_code - 1].showtime/10;
						}
						break;
					case 2:
						if(ch>='0'&&ch<='9') {
							trains[ctrl.train_code - 1].length=trains[ctrl.train_code - 1].length*10+ch-'0';
							if(trains[ctrl.train_code - 1].length>20) {
								trains[ctrl.train_code - 1].length=20;
							}
						} else if(ch==8) {
							trains[ctrl.train_code - 1].length=trains[ctrl.train_code - 1].length/10;
						}
						break;
				}
			}
		}
		ege::Sleep(50);

	}
}

void print_screen_train() {
	print_screen();
	setfillcolor(WHITE);
	bar(0, 0, 360, 620);//����ԭ��ť

	//�ѻ���Ϣ������ť��
	putimage(img_btn_enterxy, 0, 0, img_blank45170);
	putimage(img_btn_outerxy, 0, 0, img_blank45170);
	putimage(img_btn_showtime, 0, 0, img_blank45170);
	putimage(img_btn_speed, 0, 0, img_blank45170);
	putimage(img_btn_length, 0, 0, img_blank45170);
	reset_font(img_btn_enterxy);
	if (trains[ctrl.train_code - 1].enter[0] != -2)
		xyprintf(40, 5, "(%d, %d)", trains[ctrl.train_code - 1].enter[0], trains[ctrl.train_code - 1].enter[1]);
	reset_font(img_btn_outerxy);
	if (trains[ctrl.train_code - 1].outer[0] != -2)
		xyprintf(40, 5, "(%d, %d)", trains[ctrl.train_code - 1].outer[0], trains[ctrl.train_code - 1].outer[1]);
	reset_font(img_btn_showtime);
	if(in_control==1){
		xyprintf(40, 5, "%d_", trains[ctrl.train_code - 1].showtime);
	}else{
		xyprintf(40, 5, "%d", trains[ctrl.train_code - 1].showtime);
	}
	reset_font(img_btn_speed);
	if (trains[ctrl.train_code - 1].speed)
		xyprintf(40, 5, "��");
	else
		xyprintf(40, 5, "��");
	reset_font(img_btn_length);
	if(in_control==2){
		xyprintf(40, 5, "%d_", trains[ctrl.train_code - 1].length);
	}else{
		xyprintf(40, 5, "%d", trains[ctrl.train_code - 1].length);
	}
	settarget(NULL);

	//��ʾ��ť
	btn_left_a.show();
	btn_right_a.show();
	btn_enterxy.show();
	btn_outerxy.show();
	btn_showtime.show();
	btn_speed.show();
	btn_length.show();
	btn_back.show();

	//��ʾ����
	setfont(30, 0, "����");
	setcolor(BLACK);
	xyprintf(80, 35, "�𳵱�� %d", ctrl.train_code);
	xyprintf(20, 105, "�������");
	xyprintf(20, 185, "��������");
	xyprintf(20, 265, "����ʱ��");
	xyprintf(20, 345, "��ʼ�ٶ�");
	xyprintf(20, 425, "�𳵳���");
}

void reset_font(PIMAGE img) {
	settarget(img);
	setfont(30, 0, "����", img);
	setcolor(BLACK, img);
	setbkcolor(WHITE, img);
}
