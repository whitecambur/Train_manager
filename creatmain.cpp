#include <graphics.h>
#include"creatmain.h"
#include "mine_btn.h"
#include "levelmaker.h"//�ṹ���� ��������
#include "btn_fn.h"//��ť�¼�
#include "others.h"//��������
#include "trainmaker.h"//�𳵱༭������
#include"movingpic.h"


/////////////////////////////�ļ��ں�������
void print_screen();
void init_map();
void init_ctrl();
void undo(int, int);
void btnf_reset_img();
void rotate_cube(int, int);
void init_trains();

//////////////////////////////ȫ�ֱ���
MapCube map[MAP_HEIGHT][MAP_WIDTH];//��ͼ
Control ctrl;//��ť����
Train trains[20];//��

				 //////////////////////////////////ͼƬ
PIMAGE img_1;
PIMAGE img_2;
PIMAGE img_3;
PIMAGE img_4;
PIMAGE img_5;
PIMAGE img_6;
PIMAGE img_7;
PIMAGE img_8;
PIMAGE img_9;
PIMAGE img_blank;//�յ�ͼƬ
PIMAGE img_blank70;//70*70�հ�
PIMAGE img_blank70140;//70*140�հ�
PIMAGE img_blank45170;//45*170�հ�
PIMAGE img_track1;//��ֱ����ֱ��
PIMAGE img_track2;//��һ�������
PIMAGE img_track3;//������
PIMAGE img_rotate1;//��ת�����ʶ1
PIMAGE img_rotate2;//��ת�����ʶ2
PIMAGE img_rotate3;//��ת�����ʶ3
PIMAGE img_acc1;//���ٹ����ʶ1
PIMAGE img_acc2;//���ٹ����ʶ2
PIMAGE img_boom;//��ը�����ʶ
PIMAGE img_station;//����ڱ�ʶ
PIMAGE img_btn_add_track;//���ӹ����ť
PIMAGE img_btn_add_rotate;//������ת��ʶ��ť
PIMAGE img_btn_add_acc;//���Ӽ��ٱ�ʶ��ť
PIMAGE img_btn_add_boom;//���ӱ�ը��ʶ��ť
PIMAGE img_btn_clear;//������ť
PIMAGE img_btn_load;//������ť
PIMAGE img_btn_add_bind;//���������ť
PIMAGE img_btn_add_station;//��ӳ�վ��ť
PIMAGE img_btn_edit_train;//�༭�𳵰�ť
PIMAGE img_btn_start_qedit;//�������ٱ༭
PIMAGE img_btn_end_qedit;//�رտ��ٱ༭
PIMAGE img_btn_save;//�浵��ť
PIMAGE img_btn_exit;//�˳���ť
PIMAGE img_btn_left_a;//���ͷ
PIMAGE img_btn_right_a;//�Ҽ�ͷ
PIMAGE img_btn_enterxy;//���
PIMAGE img_btn_outerxy;//����
PIMAGE img_btn_showtime;//ʱ��
PIMAGE img_btn_speed;//�ٶ�
PIMAGE img_btn_length;//����
PIMAGE img_btn_back;//���ذ�ť

					/////////////////////////////////��ť
BTN btn_add_track(40, 30, 180, 100, img_btn_add_track, btnf_add_track, btnf_change_track);//��ť-�������� ���ѡ�� �Ҽ��л���������
BTN btn_add_rotate(40, 120, 180, 190, img_btn_add_rotate, btnf_add_rotate, btnf_change_rotate);//��ť-������ת��ʶ
BTN btn_add_acc(40, 210, 180, 280, img_btn_add_acc, btnf_add_acc, btnf_change_acc);//��ť-���Ӽ��ٱ�ʶ �Ҽ��л����ٷ���
BTN btn_add_boom(40, 300, 180, 370, img_btn_add_boom, btnf_add_boom);//��ť-����ը�� ����ը��Ч��δ�� ��ʱ�޷�����ը��ʱ��
BTN btn_clear(40, 390, 180, 460, img_btn_clear, BTN_NH);//��ť-����
BTN btn_load(40, 480, 180, 550, img_btn_load, btnf_load);//��ť-����
BTN btn_add_bind(200, 30, 340, 100, img_btn_add_bind, btnf_add_bind);//��ť-�������
BTN btn_add_station(200, 120, 340, 190, img_btn_add_station, btnf_add_station);//��ӳ�վ
BTN btn_edit_train(200, 210, 340, 280, img_btn_edit_train, btnf_edit_train);
BTN btn_change_qedit(200, 300, 340, 370, img_btn_start_qedit, BTN_NH);//�л����ٱ༭
BTN btn_save(200, 390, 340, 460, img_btn_save, btnf_save);//��ť-�浵
BTN btn_exit(200, 480, 340, 550, img_btn_exit, BTN_NH);//��ť-�浵
BTN btn_left_a(35, 35, 65, 65, img_btn_left_a, BTN_NH);//���ͷ��ť
BTN btn_right_a(270, 35, 300, 65, img_btn_right_a, BTN_NH);//�Ҽ�ͷ��ť
BTN btn_enterxy(170, 100, 340, 145, img_btn_enterxy, btnf_get_enterxy, btnf_reset_enterxy);//�������
BTN btn_outerxy(170, 180, 340, 225, img_btn_outerxy, btnf_get_outerxy, btnf_reset_outerxy);//��������
BTN btn_showtime(170, 260, 340, 305, img_btn_showtime, BTN_NH);//����ʱ��
BTN btn_speed(170, 340, 340, 385, img_btn_speed, BTN_NH);//�ٶ�
BTN btn_length(170, 420, 340, 465, img_btn_length, BTN_NH);//����
BTN btn_back(200, 500, 340, 570, img_btn_back, BTN_NH);//����

													   /************************************
													   ����λ��
													   (365, 10)(965, 610)
													   ***************************************/
int creatmain() {
	//����
	setbkcolor(WHITE);
	
	//���¸���ť��ͼƬ
	btnf_reset_img();

	//��ʼ������
	init_map();

	//��ʼ������
	init_ctrl();

	//��ʼ����
	init_trains();
	settextjustify(0, 2);

	print_screen();//ˢ��
	bool flag = 0;//�Ƿ���ֹ
	for (; is_run(); delay_fps(60)) {
		mouse_msg msg = { 0 };
		while (mousemsg()) {
			msg = getmouse();
			if (msg.is_left()&&msg.is_down()) { //�жϲ�ִ���������
				bool click_btn = 0;//�Ƿ����˰�ť
				if (btn_add_track.left(msg.x, msg.y)) {
					//print_screen();
					btn_add_track.set_highlight(0);//ȡ��ѡ�а�ť
					click_btn = 1;
				}
				else if (btn_add_rotate.left(msg.x, msg.y)) {
					//print_screen();
					btn_add_rotate.set_highlight(0);
					click_btn = 1;
				}
				else if (btn_add_acc.left(msg.x, msg.y)) {
					//print_screen();
					btn_add_acc.set_highlight(0);
					click_btn = 1;
				}
				else if (btn_add_boom.left(msg.x, msg.y)) {
					//print_screen();
					btn_add_boom.set_highlight(0);
					click_btn = 1;
				}
				else if (btn_clear.left(msg.x, msg.y)) {
					init_map();
					//print_screen();
					click_btn = 1;
				}
				else if (btn_add_bind.left(msg.x, msg.y)) {
					//print_screen();
					btn_add_bind.set_highlight(0);
					click_btn = 1;
				}
				else if (btn_add_station.left(msg.x, msg.y)) {
					btn_add_station.set_highlight(0);
					click_btn = 1;
				}
				else if (btn_save.left(msg.x, msg.y)) {
					//�浵 ������
					click_btn = 1;
				}
				else if (btn_load.left(msg.x, msg.y)) {
					click_btn = 1;
				}
				else if (btn_change_qedit.left(msg.x, msg.y)) {
					ctrl.qedit = !ctrl.qedit;
					if (ctrl.qedit)
						btn_change_qedit.set_img(img_btn_end_qedit);
					else
						btn_change_qedit.set_img(img_btn_start_qedit);
					click_btn = 1;
				}
				else if (btn_edit_train.left(msg.x, msg.y)) {
					click_btn = 1;
				}
				else if (btn_exit.left(msg.x, msg.y)) {
					click_btn = 1;
					blackpage(NULL);
					return 0;
				}
				if (click_btn == 0) {//ȫ����ת
					rotate_cube(msg.x, msg.y);
				}
			}
			else if (msg.is_right()&&msg.is_down()) { //�жϲ�ִ���Ҽ�����
				bool click_btn = 0;//�Ƿ����˰�ť
				if (btn_add_track.right(msg.x, msg.y)) {
					click_btn = 1;
					//print_screen();
				}
				else if (btn_add_rotate.right(msg.x, msg.y)) {
					click_btn = 1;
				}
				else if (btn_add_acc.right(msg.x, msg.y)) {
					click_btn = 1;
					//print_screen();
				}
				else if (btn_save.right(msg.x, msg.y)) {
					click_btn = 1;
				}
				else if (btn_change_qedit.right(msg.x, msg.y)) {
					ctrl.qedit = !ctrl.qedit;
					if (ctrl.qedit)
						btn_change_qedit.set_img(img_btn_end_qedit);
					else
						btn_change_qedit.set_img(img_btn_start_qedit);
					click_btn = 1;
				}
				if (click_btn == 0) { //�һ���û�е����ť ����ȫ�ֳ�������
					undo(msg.x, msg.y);
					//print_screen();
				}
				click_btn = 0;
			}
			else {//ȫ�ְ�ť��hover��hoverback�¼�
				if (btn_add_track.hover(msg.x, msg.y)) {
					btn_add_track.set_highlight(1);
				}
				if (btn_add_rotate.hover(msg.x, msg.y)) {
					btn_add_rotate.set_highlight(1);
				}
				if (btn_add_acc.hover(msg.x, msg.y)) {
					btn_add_acc.set_highlight(1);
				}
				if (btn_add_boom.hover(msg.x, msg.y)) {
					btn_add_boom.set_highlight(1);
				}
				if (btn_clear.hover(msg.x, msg.y)) {
					btn_clear.set_highlight(1);
				}
				if (btn_load.hover(msg.x, msg.y)) {
					btn_load.set_highlight(1);
				}
				if (btn_add_bind.hover(msg.x, msg.y)) {
					btn_add_bind.set_highlight(1);
				}
				if (btn_add_station.hover(msg.x, msg.y)) {
					btn_add_station.set_highlight(1);
				}
				if (btn_edit_train.hover(msg.x, msg.y)) {
					btn_edit_train.set_highlight(1);
				}
				if (btn_change_qedit.hover(msg.x, msg.y)) {
					btn_change_qedit.set_highlight(1);
				}
				if (btn_save.hover(msg.x, msg.y)) {
					btn_save.set_highlight(1);
				}
				if (btn_exit.hover(msg.x, msg.y)) {
					btn_exit.set_highlight(1);
				}
				if (btn_add_track.hoverback(msg.x, msg.y)) {
					btn_add_track.set_highlight(0);
				}
				if (btn_add_rotate.hoverback(msg.x, msg.y)) {
					btn_add_rotate.set_highlight(0);
				}
				if (btn_add_acc.hoverback(msg.x, msg.y)) {
					btn_add_acc.set_highlight(0);
				}
				if (btn_add_boom.hoverback(msg.x, msg.y)) {
					btn_add_boom.set_highlight(0);
				}
				if (btn_clear.hoverback(msg.x, msg.y)) {
					btn_clear.set_highlight(0);
				}
				if (btn_load.hoverback(msg.x, msg.y)) {
					btn_load.set_highlight(0);
				}
				if (btn_add_bind.hoverback(msg.x, msg.y)) {
					btn_add_bind.set_highlight(0);
				}
				if (btn_add_station.hoverback(msg.x, msg.y)) {
					btn_add_station.set_highlight(0);
				}
				if (btn_edit_train.hoverback(msg.x, msg.y)) {
					btn_edit_train.set_highlight(0);
				}
				if (btn_change_qedit.hoverback(msg.x, msg.y)) {
					btn_change_qedit.set_highlight(0);
				}
				if (btn_save.hoverback(msg.x, msg.y)) {
					btn_save.set_highlight(0);
				}
				if (btn_exit.hoverback(msg.x, msg.y)) {
					btn_exit.set_highlight(0);
				}
			}
		}
		print_screen();
	}
	settextjustify(CENTER_TEXT, CENTER_TEXT);
	setfont(30, 0, "����");
	return 0;
}

/****************
ˢ��ȫ����Ļ
********************/
void print_screen() {
	//����ʽ����
	setfillcolor(WHITE);
	bar(0, 0, 1000, 620);

	//��ʾ��ť
	btn_add_track.show();
	btn_add_rotate.show();
	btn_add_acc.show();
	btn_add_boom.show();
	btn_clear.show();
	btn_load.show();
	btn_add_bind.show();
	btn_add_station.show();
	btn_edit_train.show();
	btn_change_qedit.show();
	btn_save.show();
	btn_exit.show();

	//��ʾ��ͼ
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (map[i][j].type != 0) {
				switch (map[i][j].type) {//��������� �ٸ��ӱ�ʶ
										 //putimage_rotate(Ŀ��ͼ�� ԭͼ�� ���ĵ�x ���ĵ�y ���ĵ���ԭͼ���������xy ��ת�Ƕ�)
				case 1:
					putimage_rotate(NULL, img_track1, 365 + 50 * j + 25, 10 + 50 * i + 25, 0.5f, 0.5f, -PI / 2 * map[i][j].rotate, 1);
					break;
				case 2:
					putimage_rotate(NULL, img_track2, 365 + 50 * j + 25, 10 + 50 * i + 25, 0.5f, 0.5f, -PI / 2 * map[i][j].rotate, 1);
					break;
				case 3:
					putimage_rotate(NULL, img_track3, 365 + 50 * j + 25, 10 + 50 * i + 25, 0.5f, 0.5f, -PI / 2 * map[i][j].rotate, 1);
					break;
				}
				switch (map[i][j].child_type) {
				case 1://�ɱ���
					if (map[i][j].rotate_type == 1)
						putimage_transparent(NULL, img_rotate1, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					else if (map[i][j].rotate_type == -1)
						putimage_transparent(NULL, img_rotate2, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					else
						putimage_transparent(NULL, img_rotate3, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				case 2: {//���ٹ��
					if (!map[i][j].speed_type)
						putimage_transparent(NULL, img_acc1, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					else
						putimage_transparent(NULL, img_acc2, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				}
				case 3://��ը���
					putimage_transparent(NULL, img_boom, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				case 4://��
					putimage_transparent(NULL, img_station, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				}
			}
			else {//�յ�
				putimage(365 + 50 * j, 10 + 50 * i, img_blank);
			}
		}
	}
}

/***************
��ͼ��ʼ��
******************/
void init_map() {
	//��ʼ����ͼ
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			map[i][j].type = 0;
			map[i][j].rotate = 0;
			map[i][j].child_type = 0;
			map[i][j].speed_type = 0;
			map[i][j].rotate_type = 1;
			map[i][j].time1 = 0;
			map[i][j].time2 = 0;
			map[i][j].bind_num = 0;
			map[i][j].train_code = 0;
			map[i][j].station_type = 0;
		}
	}
}

/*************************
ȫ�ֳ�������
xyΪ�������
**********************/
void undo(int msg_x, int msg_y) {
	int x, y;//��������
			 //�����������õ��������� x y
	if (!in_map(msg_x, msg_y))
		return;
	x = getX(msg_x);
	y = getY(msg_y);

	if (map[y][x].type != 0) {
		if (map[y][x].child_type != 0) {//��Ϊ��ͨ���� �������Թ���
			map[y][x].speed_type = 0;
			map[y][x].rotate_type = 0;
			map[y][x].time1 = 0;
			map[y][x].time2 = 0;
			map[y][x].bind_num = 0;
			if (map[y][x].train_code) {
				//�л��Դ�Ϊ�����
				if (map[y][x].station_type) {
					//�����
					trains[map[y][x].train_code - 1].enter[0] = -2;
					trains[map[y][x].train_code - 1].enter[1] = -2;
				}
				else {
					//�ǳ���
					trains[map[y][x].train_code - 1].outer[0] = -2;
					trains[map[y][x].train_code - 1].outer[1] = -2;
				}
				map[y][x].train_code = 0;
			}

			if (map[y][x].child_type == 1) {
				//�ҵ�Ŀǰû�г�Ա����С�����
				get_bind();
			}
			map[y][x].child_type = 0;
		}
		else {//�������� ��ʼ��һ������
			map[y][x].type = 0;
			map[y][x].rotate = 0;
			map[y][x].child_type = 0;
			map[y][x].speed_type = 0;
			map[y][x].rotate_type = 0;
			map[y][x].time1 = 0;
			map[y][x].time2 = 0;
			map[y][x].bind_num = 0;
		}
	}
	mouse_msg msg = { 0 };
	wait_up();
}

/*****************
��ʼ������
************/
void init_ctrl() {
	ctrl.add_track = 1;
	ctrl.add_rotate_type = 1;
	ctrl.acc_type = 0;
	ctrl.bind_num = 1;
	ctrl.qedit = 0;
	ctrl.train_code = 1;
}

/***************
����ͼƬ
***************/
void deal_img() {
	//ͼƬ����
	img_1 = newimage();
	img_2 = newimage();
	img_3 = newimage();
	img_4 = newimage();
	img_5 = newimage();
	img_6 = newimage();
	img_7 = newimage();
	img_8 = newimage();
	img_9 = newimage();
	img_blank = newimage();
	img_blank70 = newimage();
	img_blank70140 = newimage();
	img_blank45170 = newimage();
	img_track1 = newimage();
	img_track2 = newimage();
	img_track3 = newimage();
	img_rotate1 = newimage();
	img_rotate2 = newimage();
	img_rotate3 = newimage();
	img_acc1 = newimage();
	img_acc2 = newimage();
	img_boom = newimage();
	img_station = newimage();
	img_btn_clear = newimage();
	img_btn_load = newimage();
	img_btn_add_bind = newimage();
	img_btn_add_station = newimage();
	img_btn_edit_train = newimage();
	img_btn_start_qedit = newimage();
	img_btn_end_qedit = newimage();
	img_btn_save = newimage();
	img_btn_exit = newimage();
	img_btn_left_a = newimage();
	img_btn_right_a = newimage();
	img_btn_enterxy = newimage();
	img_btn_outerxy = newimage();
	img_btn_showtime = newimage();
	img_btn_speed = newimage();
	img_btn_length = newimage();
	img_btn_back = newimage();
	img_btn_add_track = newimage(140, 70);
	img_btn_add_rotate = newimage(140, 70);
	img_btn_add_acc = newimage(140, 70);
	img_btn_add_boom = newimage(140, 70);
	getimage(img_1, "image//1.png");
	getimage(img_2, "image//2.png");
	getimage(img_3, "image//3.png");
	getimage(img_4, "image//4.png");
	getimage(img_5, "image//5.png");
	getimage(img_6, "image//6.png");
	getimage(img_7, "image//7.png");
	getimage(img_8, "image//8.png");
	getimage(img_9, "image//9.png");
	getimage(img_blank, "image//blank.png");
	getimage(img_blank70, "image//blank70.png");
	getimage(img_blank70140, "image//blank70140.png");
	getimage(img_blank45170, "image//blank45170.png");
	getimage(img_track1, "image//train_way2.png");
	getimage(img_track2, "image//train_way3.png");
	getimage(img_track3, "image//train_way7.png");
	getimage(img_rotate1, "image//shun_.png");
	getimage(img_rotate2, "image//ni_.png");
	getimage(img_rotate3, "image//rotate.png");
	getimage(img_acc1, "image//speedup_.png");
	getimage(img_acc2, "image//speedlow_.png");
	getimage(img_boom, "image//boom.png");
	getimage(img_station, "image//station.png");
	getimage(img_btn_clear, "image//clear.png");
	getimage(img_btn_load, "image//load.png");
	getimage(img_btn_add_bind, "image//add_bind.png");
	getimage(img_btn_add_station, "image//add_station.png");
	getimage(img_btn_edit_train, "image//edit_train.png");
	getimage(img_btn_start_qedit, "image//start_qedit.png");
	getimage(img_btn_end_qedit, "image//end_qedit.png");
	getimage(img_btn_save, "image//save.png");
	getimage(img_btn_exit, "image//exit.png");
	getimage(img_btn_left_a, "image//left_a.png");
	getimage(img_btn_right_a, "image//right_a.png");
	getimage(img_btn_back, "image//back.png");

	getimage(img_btn_enterxy, img_blank45170, 0, 0, 170, 45);
	getimage(img_btn_outerxy, img_blank45170, 0, 0, 170, 45);
	getimage(img_btn_showtime, img_blank45170, 0, 0, 170, 45);
	getimage(img_btn_speed, img_blank45170, 0, 0, 170, 45);
	getimage(img_btn_length, img_blank45170, 0, 0, 170, 45);

	PIMAGE temp = newimage();
	getimage(temp, "image//add_track.png");
	putimage(img_btn_add_track, 0, 0, temp);
	putimage(img_btn_add_track, 70, 0, img_blank70);
	putimage(img_btn_add_track, 80, 10, img_track1);

	getimage(temp, "image//add_rotate.png");
	putimage(img_btn_add_rotate, 0, 0, temp);
	putimage(img_btn_add_rotate, 70, 0, img_blank70);
	putimage(img_btn_add_rotate, 80, 10, img_rotate1);

	getimage(temp, "image//add_acc.png");
	putimage(img_btn_add_acc, 0, 0, temp);
	putimage(img_btn_add_acc, 70, 0, img_blank70);
	putimage(img_btn_add_acc, 80, 10, img_acc1);

	getimage(temp, "image//add_boom.png");
	putimage(img_btn_add_boom, 0, 0, temp);
	putimage(img_btn_add_boom, 70, 0, img_blank70);
	putimage(img_btn_add_boom, 80, 10, img_boom);
	delimage(temp);
}

/***************
��ť���¼���ͼƬ
*******************/
void btnf_reset_img() {
	btn_add_track.set_img(img_btn_add_track);
	btn_add_rotate.set_img(img_btn_add_rotate);
	btn_add_acc.set_img(img_btn_add_acc);
	btn_add_boom.set_img(img_btn_add_boom);
	btn_clear.set_img(img_btn_clear);
	btn_load.set_img(img_btn_load);
	btn_add_bind.set_img(img_btn_add_bind);
	btn_add_station.set_img(img_btn_add_station);
	btn_edit_train.set_img(img_btn_edit_train);
	btn_change_qedit.set_img(img_btn_start_qedit);
	btn_save.set_img(img_btn_save);
	btn_exit.set_img(img_btn_exit);
	btn_left_a.set_img(img_btn_left_a);
	btn_right_a.set_img(img_btn_right_a);
	btn_enterxy.set_img(img_btn_enterxy);
	btn_outerxy.set_img(img_btn_outerxy);
	btn_showtime.set_img(img_btn_showtime);
	btn_speed.set_img(img_btn_speed);
	btn_length.set_img(img_btn_length);
	btn_back.set_img(img_btn_back);
}

/**************
ȫ����ת����
***************/
void rotate_cube(int msg_x, int msg_y) {
	int x, y;//��������
			 //�����������õ��������� x y
	if (!in_map(msg_x, msg_y))
		return;
	x = getX(msg_x);
	y = getY(msg_y);

	//����ڷ��Ľǵ���Ϸ�߽�
	if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1) {
		wait_up();
		return;
	}

	if (map[y][x].type != 0) {
		map[y][x].rotate = (map[y][x].rotate + 1) % 4;
	}

	mouse_msg msg = { 0 };
	wait_up();
	return;
}

void init_trains() {
	for (int i = 0; i < 20; i++) {
		trains[i].code = i;
		trains[i].enter[0] = -2;
		trains[i].enter[1] = -2;
		trains[i].outer[0] = -2;
		trains[i].outer[1] = -2;
		trains[i].showtime = 1;
		trains[i].speed = 0;
		trains[i].length = 1;
	}
}
