#define gameflag_ready -1
#define gameflag_init 0
#define gameflag_pause 1
#define gameflag_win 2
#define gameflag_out 3
#define gameflag_crash 4
#define gameflag_wrong 5
#define gameflag_return 6
#define gameflag_exit 7
#define gameflag_boost 8
#include<stdio.h>
#include"button.h"
#include"playing.h"
#include"movingpic.h"
#include"train.h"
#include"draw.h"
static PIMAGE background[3] = { NULL };
static PIMAGE msg_boxpic = NULL;
static PIMAGE btnpic_start = NULL;
static PIMAGE btnpic_pause = NULL;
static PIMAGE btnpic_continue = NULL;
static PIMAGE btnpic_return = NULL;
static PIMAGE btnpic_exit = NULL;
static PIMAGE btnpic_next = NULL;
int loadlevel(cube*map[][12], train**mytrain, int*train_num, const char*ch);
int game_msg_box(int flag);						//��Ϸ���������ʾ��
int in_game(const char*ch) {
	int i,j;
	int the_time = 0;
	class cube*map[12][12] = { NULL };
	int train_num = 0;				//������
	int train_passed = 0;			//ͨ���Ļ�����
	class train *mytrain[20] = { NULL };
	mouse_msg mymouse = { 0 };
	PIMAGE page = newimage(1000, 620);

	setfont(30, 0, "����", page);
	setcolor(RED,page);
	setbkmode(TRANSPARENT, page);
	settextjustify(CENTER_TEXT, CENTER_TEXT, page);

	int nextstep = 0;				//���ؿ�����Ӧ�ø�ɶ
	if (loadlevel(map, mytrain, &train_num,ch) == 0) {
		int flag = gameflag_ready;			//�ж���Ϸ����ı�־,-1:���� 0:��Ϸ�� 1:pause 2:ʤ�� 3:�ѹ� 4:��ײ 5:������ 6:���� 7:ֱ���˳� 8:�����ƽ�
		button start, pause, game_continue, game_return, back;
		start.creat(60, 100, 100, 50, btnpic_start);
		pause.creat(60, 100, 100, 50, btnpic_pause);
		game_continue.creat(60, 100, 100, 50, btnpic_continue);
		game_return.creat(60, 200, 100, 50, btnpic_return);
		back.creat(60, 300, 100, 50, btnpic_exit);
		//��һ�λ�ͼ
		settarget(page);
		ege::putimage(0, 0, background[0]);
		start.action(mymouse);
		back.action(mymouse);
		for (i = 0; i < 12; i++) {
			for (j = 0; j < 12; j++) {
				map[i][j]->draw(j, i, 70);
			}
		}
		settarget(NULL);

		blackpage(page);
		putimage(0, 0, page);
		
		while (flag == gameflag_ready) {
			if (mousemsg()) {
				mymouse = { 0 };
			}
			while (mousemsg() && mymouse.is_up() == false) {
				mymouse = getmouse();
			}
			putimage(0, 0, page);
			if (start.action(mymouse) == 1) {
				mymouse = { 0 };
				flag = gameflag_init;
			}
			if (back.action(mymouse) == 1) {
				mymouse = { 0 };
				flag = gameflag_exit;
			}
			ege::Sleep(50);
		}

		for (; flag == gameflag_init&&is_run(); delay_fps(60)) {
			settarget(page);
			cleardevice();
			ege::putimage(0, 0, background[0]);
			if (mousemsg()) {
				mymouse = { 0 };
			}
			while (mousemsg() && mymouse.is_up() == false) {
				mymouse = getmouse();
			}
			
			for (i = 0; i < 12; i++) {
				for (j = 0; j < 12; j++) {
					if (mymouse.x > j * 50 + mapx && mymouse.x<j * 50 + 50 + mapx && mymouse.y>i * 50 + mapy && mymouse.y < i * 50 + 50 + mapy) {
						if (mymouse.is_down()) {
							map[i][j]->press(1, map);
							map[i][j]->draw(j, i, 50);
							mymouse = { 0 };
						}
						else {
							
							map[i][j]->draw(j, i,200);
						}
					}
					else {
						
						map[i][j]->draw(j, i, 70);
					}
					//rectangle(j * 50 + 150, i * 50 + 10, j * 50 + 200, i * 50 + 60);
				}
			}
			
			for (i = 0; i < train_num&&flag==gameflag_init; i++) {
				flag = mytrain[i]->action(map);
				if (flag == gameflag_boost) {
					train_passed++;
					flag = gameflag_init;
				}
			}
			
			//����Ϊ���水ť�Ĺ�������
			if (pause.action(mymouse) == 1) {							//��ͣ
				mymouse = { 0 };
				settarget(NULL);
				flag = gameflag_pause;
				while (flag == gameflag_pause) {
					if (mousemsg()) {
						mymouse = { 0 };
					}
					while (mousemsg() && mymouse.is_up() == false) {
						mymouse = getmouse();
					}
					putimage(0, 0, page);
					if (game_continue.action(mymouse) == 1) {			//��ͣ�м���
						mymouse = { 0 };
						flag = gameflag_init;
					}
					if (game_return.action(mymouse) == 1) {				//��ͣ������
						mymouse = { 0 };
						flag = gameflag_return;
					}
					if (back.action(mymouse) == 1) {					//��ͣ�з��ز˵�
						mymouse = { 0 };
						flag = gameflag_exit;
					}
					Sleep(30);
				}
				settarget(page);
			}
			if (game_return.action(mymouse) == 1) {
				mymouse = { 0 };
				flag = gameflag_return;
			}
			if (back.action(mymouse) == 1) {
				mymouse = { 0 };
				flag = gameflag_exit;
			}
			if (train_num == train_passed) {
				flag = gameflag_win;
			}
			settarget(NULL);
			if (flag == gameflag_init) {
				ege::putimage(0, 0, page);
			}
			//ege::Sleep(15);
		}
		nextstep = game_msg_box(flag);
		start.del_btn();
		pause.del_btn();
		game_continue.del_btn();
		game_return.del_btn();
		back.del_btn();
	}

	//����Ϊ�����ڴ�
	for (i = 0; i < 12; i++) {
		for (j = 0; j < 12; j++) {
			if (map[i][j] != NULL) {
				map[i][j]->delete_cube();
				delete map[i][j];
				map[i][j] = NULL;
			}
		}
	}
	for (i = 0; i < train_num; i++) {
		if (mytrain[i] != NULL) {
			mytrain[i]->delete_train();
			delete mytrain[i];
			mytrain[i] = NULL;
		}
	}
	blackpage(NULL);
	delimage(page);
	page = NULL;
	return nextstep;
}
int loadlevel(cube*map[][12], train**mytrain, int *train_num, const char*ch) {
	int i = 0, j = 0;
	FILE*p = NULL;
	char level[30]="";
	int type = 0;
	int shape = 0;
	int mod1 = 0, mod2 = 0;
	int t_inx = 0, t_iny = 0, t_out = 0, t_speed = 0, t_length = 0, t_time = 0;
		if ((p = fopen(ch, "r" ))!= NULL) {
			int error = 0;									//�ؿ���ȡ�����ʶ
			for (i = 0; i < 12 && error == 0; i++) {
				for (j = 0; j < 12 && error == 0; j++) {
					fscanf_s(p, "type:%d\n",&type);
					switch (type) {
					case 0:
						map[i][j] = new empty_cube;
						map[i][j]->create(0, 0);
						break;
					case 1:
						map[i][j] = new normal_cube;
						fscanf(p, "shape:%d\n", &shape);
						map[i][j]->create(shape, 1);
						map[i][j]->get_mode(0);
						break;
					case 2:
						map[i][j] = new changable_cube;
						fscanf(p, "shape:%d\n", &shape);
						map[i][j]->create(shape, 2);
						fscanf(p, "trans_way:%d\n", &mod1);
						switch (mod1) {
						case -1:map[i][j]->get_mode(2); break;
						case 0:map[i][j]->get_mode(0); break;
						case 1:map[i][j]->get_mode(1); break;
						}
						break;
					case 3:
						map[i][j] = new speed_cube;
						fscanf(p, "shape:%d\n", &shape);
						map[i][j]->create(shape, 3);
						fscanf(p, "speed_way:%d\n", &mod1);
						map[i][j]->get_mode(2-mod1);
						break;
					case 4:
						map[i][j] = new normal_cube;
						fscanf(p, "shape:%d\n", &shape);
						map[i][j]->create(shape, 1);
						map[i][j]->get_mode(0);
						break;
					case 5:
						map[i][j] = new changable_cube;
						fscanf(p, "shape:%d\n", &shape);
						map[i][j]->create(shape, 2);
						fscanf(p, "trans_way:%d\n", &mod1);
						fscanf(p, "connection:%d\n", &mod2);
						switch (mod1) {
						case -1:map[i][j]->get_mode(mod2 * 10 + 2); break;
						case 0:map[i][j]->get_mode(mod2 * 10 + 0); break;
						case 1:map[i][j]->get_mode(mod2 * 10 + 1); break;
						}
						break;
					case 6:
						map[i][j] = new normal_cube;
						fscanf(p, "shape:%d\n", &shape);
						map[i][j]->create(shape, 1);
						fscanf(p, "station_code:%d\n", &shape);
						map[i][j]->get_mode(shape);
						break;
					default:
						map[i][j] = new empty_cube;
						map[i][j]->create(0, 0);
						break;
					}
				}
			}
			while (!feof(p) && error == 0) {
				mytrain[*train_num] = new train;
				if (fscanf(p, "enter:%d,%d\nouter:%d\nshowtime:%d\nspeed:%d\nlength:%d\n", &t_inx, &t_iny, &t_out, &t_time, &t_speed, &t_length) == 6) {
					if (t_length < 1) {
						error = 1;
					}
					else {
						mytrain[*train_num]->creat(t_inx, t_iny, t_length, t_speed + 1, t_out, t_time + 1);
						(*train_num) = (*train_num) + 1;
					}
				}
				else {
					error = 1;
				}
			}
			fclose(p);
			if (error == 1) {
				MessageBox(NULL, TEXT("�ؿ��ļ�����"), TEXT("�ؿ���ȡ����"), MB_SETFOREGROUND);
				return 1;
			}
		}
		else {
			MessageBox(NULL, TEXT("�Ҳ�����Ӧ�ؿ��ļ�"), TEXT("�ؿ���ȡ����"), MB_SETFOREGROUND);
			return 1;
		}
	return 0;
}

int game_msg_box(int flag) {
	int run = 1;			//ά�ֽ���
	int nextstep = 0;		//��һ��Ҫ������
	mouse_msg mymouse = { 0 };
	button game_back, game_return, game_next;
	switch (flag) {
	case gameflag_win:
		game_back.creat(250, 400, 100, 50, btnpic_exit);
		game_return.creat(450, 400, 100, 50, btnpic_return);
		game_next.creat(650, 400, 100, 50, btnpic_next);
		blackpage(NULL, 5);
		putimage(200, 150, msg_boxpic);
		while (run) {
			if (mousemsg()) {
				mymouse = { 0 };
			}
			while (mousemsg() && mymouse.is_up() == false) {
				mymouse = getmouse();
			}
			if (game_back.action(mymouse) == 1) {
				mymouse = { 0 };
				nextstep = 0;
				run = 0;
			}
			if (game_return.action(mymouse) == 1) {
				mymouse = { 0 };
				nextstep = 1;
				run = 0;
			}
			if (game_next.action(mymouse) == 1) {
				mymouse = { 0 };
				nextstep = 2;
				run = 0;
			}
			ege::Sleep(50);
		}
		break;
	case gameflag_crash:case gameflag_out:case gameflag_wrong:
		game_back.creat(300, 400, 100, 50, btnpic_exit);
		game_return.creat(600, 400, 100, 50, btnpic_return);
		blackpage(NULL, 5);
		putimage(200, 150, msg_boxpic);
		while (run) {
			if (mousemsg()) {
				mymouse = { 0 };
			}
			while (mousemsg() && mymouse.is_up() == false) {
				mymouse = getmouse();
			}
			if (game_back.action(mymouse) == 1) {
				mymouse = { 0 };
				nextstep = 0;
				run = 0;
			}
			if (game_return.action(mymouse) == 1) {
				mymouse = { 0 };
				nextstep = 1;
				run = 0;
			}
			ege::Sleep(50);
		}
		break;
	case gameflag_exit:
		nextstep = 0;
		break;
	case gameflag_return:
		nextstep = 1;
		break;
	}
	game_back.del_btn(); game_return.del_btn(); game_next.del_btn();
	return nextstep;										//0���˻ز˵�   1������   2����һ��
}

int load_background() {
	background[0] = newimage(1000, 620);
	getimage(background[0], "image//gameback1.png");
	background[1] = newimage(1000, 620);
	getimage(background[1], "image//gameback2.png");
	background[2] = newimage(1000, 620);
	getimage(background[2], "image//gameback3.png");
	msg_boxpic = newimage(600, 300);
	getimage(background[2], "image//msg_box.png");
	btnpic_start = newimage(100, 150);
	getimage(btnpic_start, "image//btn_start.png");
	btnpic_pause = newimage(100, 150);
	getimage(btnpic_pause, "image//btn_pause.png");
	btnpic_continue = newimage(100, 150);
	getimage(btnpic_continue, "image//btn_continue.png");
	btnpic_return = newimage(100, 150);
	getimage(btnpic_return, "image//btn_return.png");
	btnpic_exit = newimage(100, 150);
	getimage(btnpic_exit, "image//btn_exit.png");
	btnpic_next = newimage(100, 150);
	getimage(btnpic_next, "image//btn_next.png");
	return 0;
}