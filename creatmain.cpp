#include <graphics.h>
#include"creatmain.h"
#include "mine_btn.h"
#include "levelmaker.h"//结构定义 常量定义
#include "btn_fn.h"//按钮事件
#include "others.h"//其他函数
#include "trainmaker.h"//火车编辑器函数
#include"movingpic.h"


/////////////////////////////文件内函数声明
void print_screen();
void init_map();
void init_ctrl();
void undo(int, int);
void btnf_reset_img();
void rotate_cube(int, int);
void init_trains();

//////////////////////////////全局变量
MapCube map[MAP_HEIGHT][MAP_WIDTH];//地图
Control ctrl;//按钮控制
Train trains[20];//火车

				 //////////////////////////////////图片
PIMAGE img_1;
PIMAGE img_2;
PIMAGE img_3;
PIMAGE img_4;
PIMAGE img_5;
PIMAGE img_6;
PIMAGE img_7;
PIMAGE img_8;
PIMAGE img_9;
PIMAGE img_blank;//空地图片
PIMAGE img_blank70;//70*70空白
PIMAGE img_blank70140;//70*140空白
PIMAGE img_blank45170;//45*170空白
PIMAGE img_track1;//竖直方向直道
PIMAGE img_track2;//第一象限弯道
PIMAGE img_track3;//四向轨道
PIMAGE img_rotate1;//旋转轨道标识1
PIMAGE img_rotate2;//旋转轨道标识2
PIMAGE img_rotate3;//旋转轨道标识3
PIMAGE img_acc1;//加速轨道标识1
PIMAGE img_acc2;//加速轨道标识2
PIMAGE img_boom;//爆炸轨道标识
PIMAGE img_station;//出入口标识
PIMAGE img_btn_add_track;//增加轨道按钮
PIMAGE img_btn_add_rotate;//增加旋转标识按钮
PIMAGE img_btn_add_acc;//增加加速标识按钮
PIMAGE img_btn_add_boom;//增加爆炸标识按钮
PIMAGE img_btn_clear;//清屏按钮
PIMAGE img_btn_load;//读档按钮
PIMAGE img_btn_add_bind;//添加联动按钮
PIMAGE img_btn_add_station;//添加车站按钮
PIMAGE img_btn_edit_train;//编辑火车按钮
PIMAGE img_btn_start_qedit;//开启快速编辑
PIMAGE img_btn_end_qedit;//关闭快速编辑
PIMAGE img_btn_save;//存档按钮
PIMAGE img_btn_exit;//退出按钮
PIMAGE img_btn_left_a;//左箭头
PIMAGE img_btn_right_a;//右箭头
PIMAGE img_btn_enterxy;//入口
PIMAGE img_btn_outerxy;//出口
PIMAGE img_btn_showtime;//时间
PIMAGE img_btn_speed;//速度
PIMAGE img_btn_length;//长度
PIMAGE img_btn_back;//返回按钮

					/////////////////////////////////按钮
BTN btn_add_track(40, 30, 180, 100, img_btn_add_track, btnf_add_track, btnf_change_track);//按钮-增加铁轨 左键选中 右键切换铁轨类型
BTN btn_add_rotate(40, 120, 180, 190, img_btn_add_rotate, btnf_add_rotate, btnf_change_rotate);//按钮-增加旋转标识
BTN btn_add_acc(40, 210, 180, 280, img_btn_add_acc, btnf_add_acc, btnf_change_acc);//按钮-增加加速标识 右键切换加速方向
BTN btn_add_boom(40, 300, 180, 370, img_btn_add_boom, btnf_add_boom);//按钮-增加炸弹 由于炸弹效果未定 暂时无法设置炸弹时间
BTN btn_clear(40, 390, 180, 460, img_btn_clear, BTN_NH);//按钮-清屏
BTN btn_load(40, 480, 180, 550, img_btn_load, btnf_load);//按钮-读档
BTN btn_add_bind(200, 30, 340, 100, img_btn_add_bind, btnf_add_bind);//按钮-添加联动
BTN btn_add_station(200, 120, 340, 190, img_btn_add_station, btnf_add_station);//添加车站
BTN btn_edit_train(200, 210, 340, 280, img_btn_edit_train, btnf_edit_train);
BTN btn_change_qedit(200, 300, 340, 370, img_btn_start_qedit, BTN_NH);//切换快速编辑
BTN btn_save(200, 390, 340, 460, img_btn_save, btnf_save);//按钮-存档
BTN btn_exit(200, 480, 340, 550, img_btn_exit, BTN_NH);//按钮-存档
BTN btn_left_a(35, 35, 65, 65, img_btn_left_a, BTN_NH);//左箭头按钮
BTN btn_right_a(270, 35, 300, 65, img_btn_right_a, BTN_NH);//右箭头按钮
BTN btn_enterxy(170, 100, 340, 145, img_btn_enterxy, btnf_get_enterxy, btnf_reset_enterxy);//入口坐标
BTN btn_outerxy(170, 180, 340, 225, img_btn_outerxy, btnf_get_outerxy, btnf_reset_outerxy);//出口坐标
BTN btn_showtime(170, 260, 340, 305, img_btn_showtime, BTN_NH);//出现时间
BTN btn_speed(170, 340, 340, 385, img_btn_speed, BTN_NH);//速度
BTN btn_length(170, 420, 340, 465, img_btn_length, BTN_NH);//长度
BTN btn_back(200, 500, 340, 570, img_btn_back, BTN_NH);//返回

													   /************************************
													   网格位置
													   (365, 10)(965, 610)
													   ***************************************/
int creatmain() {
	//窗口
	setbkcolor(WHITE);
	
	//重新给按钮赋图片
	btnf_reset_img();

	//初始化网格
	init_map();

	//初始化控制
	init_ctrl();

	//初始化火车
	init_trains();
	settextjustify(0, 2);

	print_screen();//刷屏
	bool flag = 0;//是否终止
	for (; is_run(); delay_fps(60)) {
		mouse_msg msg = { 0 };
		while (mousemsg()) {
			msg = getmouse();
			if (msg.is_left()&&msg.is_down()) { //判断并执行左键操作
				bool click_btn = 0;//是否点击了按钮
				if (btn_add_track.left(msg.x, msg.y)) {
					//print_screen();
					btn_add_track.set_highlight(0);//取消选中按钮
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
					//存档 不清屏
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
				if (click_btn == 0) {//全局旋转
					rotate_cube(msg.x, msg.y);
				}
			}
			else if (msg.is_right()&&msg.is_down()) { //判断并执行右键操作
				bool click_btn = 0;//是否点击了按钮
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
				if (click_btn == 0) { //右击且没有点击按钮 启动全局撤销功能
					undo(msg.x, msg.y);
					//print_screen();
				}
				click_btn = 0;
			}
			else {//全局按钮的hover与hoverback事件
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
	setfont(30, 0, "宋体");
	return 0;
}

/****************
刷新全局屏幕
********************/
void print_screen() {
	//覆盖式清屏
	setfillcolor(WHITE);
	bar(0, 0, 1000, 620);

	//显示按钮
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

	//显示地图
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			if (map[i][j].type != 0) {
				switch (map[i][j].type) {//先贴出轨道 再附加标识
										 //putimage_rotate(目标图像 原图像 中心点x 中心点y 中心点在原图的坐标比例xy 旋转角度)
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
				case 1://可变轨道
					if (map[i][j].rotate_type == 1)
						putimage_transparent(NULL, img_rotate1, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					else if (map[i][j].rotate_type == -1)
						putimage_transparent(NULL, img_rotate2, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					else
						putimage_transparent(NULL, img_rotate3, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				case 2: {//加速轨道
					if (!map[i][j].speed_type)
						putimage_transparent(NULL, img_acc1, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					else
						putimage_transparent(NULL, img_acc2, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				}
				case 3://爆炸轨道
					putimage_transparent(NULL, img_boom, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				case 4://口
					putimage_transparent(NULL, img_station, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
					break;
				}
			}
			else {//空地
				putimage(365 + 50 * j, 10 + 50 * i, img_blank);
			}
		}
	}
}

/***************
地图初始化
******************/
void init_map() {
	//初始化地图
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
全局撤销功能
xy为鼠标坐标
**********************/
void undo(int msg_x, int msg_y) {
	int x, y;//网格坐标
			 //根据鼠标坐标得到网格坐标 x y
	if (!in_map(msg_x, msg_y))
		return;
	x = getX(msg_x);
	y = getY(msg_y);

	if (map[y][x].type != 0) {
		if (map[y][x].child_type != 0) {//变为普通铁轨 其他属性归零
			map[y][x].speed_type = 0;
			map[y][x].rotate_type = 0;
			map[y][x].time1 = 0;
			map[y][x].time2 = 0;
			map[y][x].bind_num = 0;
			if (map[y][x].train_code) {
				//有火车以此为出入口
				if (map[y][x].station_type) {
					//是入口
					trains[map[y][x].train_code - 1].enter[0] = -2;
					trains[map[y][x].train_code - 1].enter[1] = -2;
				}
				else {
					//是出口
					trains[map[y][x].train_code - 1].outer[0] = -2;
					trains[map[y][x].train_code - 1].outer[1] = -2;
				}
				map[y][x].train_code = 0;
			}

			if (map[y][x].child_type == 1) {
				//找到目前没有成员的最小的组号
				get_bind();
			}
			map[y][x].child_type = 0;
		}
		else {//撤销铁轨 初始化一切属性
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
初始化控制
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
处理图片
***************/
void deal_img() {
	//图片操作
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
按钮重新加载图片
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
全局旋转功能
***************/
void rotate_cube(int msg_x, int msg_y) {
	int x, y;//网格坐标
			 //根据鼠标坐标得到网格坐标 x y
	if (!in_map(msg_x, msg_y))
		return;
	x = getX(msg_x);
	y = getY(msg_y);

	//如果在非四角的游戏边界
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
