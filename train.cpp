#include<stdlib.h>
#include"train.h"
#include"movingpic.h"
#include"draw.h"
static PIMAGE waypic0;
static PIMAGE waypic1;
static PIMAGE waypic2;
static PIMAGE waypic3;
static PIMAGE waypic4;
static PIMAGE waypic5;
static PIMAGE waypic6;
static PIMAGE waypic7;
static PIMAGE trainpic1_head;
static PIMAGE trainpic1_mid;
static PIMAGE outer;
static PIMAGE trans1_pic,trans2_pic,trans3_pic;
static PIMAGE speedup_pic,speeddown_pic;
int load_pic() {
	waypic0 = newimage(50, 50);
	waypic1 = newimage(50, 50);

	getimage(waypic1, "image//train_way1.png");					
	waypic2 = newimage(50, 50);

	getimage(waypic2, "image//train_way2.png");
	waypic3 = newimage(50, 50);
	getimage(waypic3, "image//train_way3.png");
	waypic4 = newimage(50, 50);
	getimage(waypic4, "image//train_way4.png");
	waypic5 = newimage(50, 50);
	getimage(waypic5, "image//train_way5.png");
	waypic6 = newimage(50, 50);
	getimage(waypic6, "image//train_way6.png");
	waypic7 = newimage(50, 50);
	getimage(waypic7, "image//train_way7.png");
	trainpic1_head = newimage(50, 50);
	getimage(trainpic1_head, "image//train1_head.png");
	trainpic1_mid = newimage(50, 50);
	getimage(trainpic1_mid, "image//train1_mid.png");
	trans1_pic = newimage(50, 50);
	getimage(trans1_pic, "image//shun.png");
	trans2_pic = newimage(50, 50);
	getimage(trans2_pic, "image//ni.png");
	trans3_pic = newimage(50, 50);
	getimage(trans3_pic, "image//ro_360.png");
	speedup_pic = newimage(50, 50);
	getimage(speedup_pic, "image//speedup.png");
	speeddown_pic = newimage(50, 50);
	getimage(speeddown_pic, "image//speeddown.png");
	return 0;
}
int cube::get_type() {
	return this->type;
}
void cube::add_train(int num) {
	this->train_num += num;
}
int cube::get_trainnum() {
	return this->train_num;
}
struct train_way cube::get_msg() {
	return this->the_way;
}
void cube::delete_cube() {
	this->pimg = NULL;
	this->sign = NULL;
	return;
}
void cube::create(int pic_type,int type) {
	switch (pic_type) {
	case 0:this->pimg = waypic0; this->the_way = { 0,0,0,0 }; break;
	case 1:this->pimg = waypic1; this->the_way = { 1,0,3,0 }; break;		//竖轨道
	case 2:this->pimg = waypic2; this->the_way = { 2,0,4,0 }; break;		//横轨道
	case 3:this->pimg = waypic3; this->the_way = { 1,-1,2,1 }; break;		//第一象限弯轨道
	case 4:this->pimg = waypic4; this->the_way = { 1,1,4,-1 }; break;		//第二象限弯轨道
	case 5:this->pimg = waypic5; this->the_way = { 3,-1,4,1 }; break;		//第三象限弯轨道
	case 6:this->pimg = waypic6; this->the_way = { 3,1,2,-1 }; break;		//第四象限弯轨道
	case 7:this->pimg = waypic7; this->the_way = { 5,0,5,0 }; break;		//交叉横竖轨道
	}
	this->sign = NULL;
	this->rotate = 0;
	this->train_num = 0;
	this->type = type;
}
void cube::draw(int x,int y,int alpha) {
	putimage_rotate(NULL, this->pimg, 50 * x + 25 + mapx, 50 * y + 25 + mapy, 0.5f, 0.5f, this->rotate, 1);
	if (this->sign != NULL) {
		putimage_alphatransparent(NULL, this->sign, 50 * x + mapx, 50 * y + mapy, BLACK, 150);
	}
	if (this->type == 1 && this->get_mode(-1) != 0) {
		xyprintf(50 * x + 25 + mapx, 50 * y + 25 + mapy, "%d", this->get_mode(-1));
	}
}
int normal_cube::get_mode(int num) {
	if (num == -1) {
		return this->enter_num;
	}
	else {
		this->enter_num = num;
		return 0;
	}
}
int changable_cube::get_mode(int trans_way) {
	if (trans_way == -1) {
		return this->trans_team;
	}else{
		this->trans_way = trans_way % 10;
		this->trans_team = trans_way / 10;
		this->rotate_cur = 0;
		switch (trans_way % 10) {
		case 0:this->sign = trans3_pic; break;
		case 1:this->sign = trans1_pic; break;
		case 2:this->sign = trans2_pic; break;
		}
	}
	return 0;
}
void changable_cube::draw(int x, int y,int alpha) {
	if (this->rotate_cur < this->rotate - 0.00001) {
		this->rotate_cur += PI / 6;
	}
	if (this->rotate_cur > this->rotate + 0.00001) {
		this->rotate_cur -= PI / 6;
	}
	putimage_rotate(NULL, this->pimg, 50 * x + 25 + mapx, 50 * y + 25 + mapy, 0.5f, 0.5f, this->rotate_cur, 1);
	PIMAGE pic = newimage(50, 50);
	switch (this->trans_team) {
	case 0:setbkcolor(WHITE, pic); break;
	case 1:setbkcolor(RED, pic); break;
	case 2:setbkcolor(YELLOW, pic); break;
	case 3:setbkcolor(GREEN, pic); break;
	case 4:setbkcolor(BLUE, pic); break;
	case 5:setbkcolor(MAGENTA, pic); break;
	case 6:setbkcolor(BROWN, pic); break;
	case 7:setbkcolor(LIGHTGRAY, pic); break;
	case 8:setbkcolor(LIGHTCYAN, pic); break;
	case 9:setbkcolor(DARKGRAY, pic); break;
	}
	putimage_transparent(pic, this->sign, 0, 0, EGERGB(255, 255, 255));
	putimage_alphatransparent(NULL, pic, 50 * x + mapx, 50 * y + mapy, BLACK, alpha);
	delimage(pic);
}
void changable_cube::press(int type, class cube *map[][12]) {
	if (this->trans_team == 0 || type == 0) {
		if (this->train_num == 0) {
			if (this->trans_way == 0) {					//转一圈类型
				if ((this->the_way).in_type1 == 4) {
					(this->the_way).in_type1 = 1;
				}
				else {
					(this->the_way).in_type1++;
				}
				if ((this->the_way).in_type2 == 4) {
					(this->the_way).in_type2 = 1;
				}
				else {
					(this->the_way).in_type2++;
				}
				this->rotate -= PI / 2;
			}
			else if (this->trans_way == 1) {			//顺时针转类型
				if ((this->the_way).in_type1 == 4) {
					(this->the_way).in_type1 = 1;
				}
				else {
					(this->the_way).in_type1++;
				}
				if ((this->the_way).in_type2 == 4) {
					(this->the_way).in_type2 = 1;
				}
				else {
					(this->the_way).in_type2++;
				}
				this->trans_way = 2;
				this->rotate -= PI / 2;
				this->sign = trans2_pic;
			}
			else if (this->trans_way == 2) {			//逆时针转类型
				if ((this->the_way).in_type1 == 1) {
					(this->the_way).in_type1 = 4;
				}
				else {
					(this->the_way).in_type1--;
				}
				if ((this->the_way).in_type2 == 1) {
					(this->the_way).in_type2 = 4;
				}
				else {
					(this->the_way).in_type2--;
				}
				this->trans_way = 1;
				this->rotate += PI / 2;
				this->sign = trans1_pic;
			}
		}
	}
	else {
		int i, j, flag = 0;
		for (i = 0; i < 12 && flag == 0; i++) {
			for (j = 0; j < 12 && flag == 0; j++) {
				if (map[i][j]->get_type() == 2 && map[i][j]->get_mode(-1) == this->trans_team) {
					if (map[i][j]->get_trainnum() != 0) {
						flag = 1;
					}
				}
			}
		}
		if (flag == 0) {
			for (i = 0; i < 12; i++) {
				for (j = 0; j < 12; j++) {
					if (map[i][j]->get_type() == 2 && map[i][j]->get_mode(-1) == this->trans_team) {
						map[i][j]->press(0, map);
					}
				}
			}
		}
		else {
			/*无法完成改变提示*/
		}
	}
}
int speed_cube::get_mode(int type) {
	if (type == -1) {
		return this->speedtype;
	}
	else {
		this->speedtype = type;
		switch (type) {
		case 1:this->sign = speeddown_pic; break;
		case 2:this->sign = speedup_pic; break;
		}
		return 0;
	}
}
void train::creat(int x, int y, int length, int speed, int fina, int init_time) {
	int i;
	int dx = 0, dy = 0;//后面车厢的位置偏移量
	this->x = x;
	this->y = y;
	if (y == 12) {
		this->toward = 1;
	}
	if (x == -1) {
		this->toward = 2;
	}
	if (y == -1) {
		this->toward = 3;
	}
	if (x == 12) {
		this->toward = 4;
	}
	this->length = length;
	this->speed = speed;
	this->fina = fina;
	this->time = 1;
	this->init_time = init_time;
	this->is_turn = 0;
	if (length > 0) {
		this->boxes = (struct train_box*)malloc(sizeof(struct train_box)*(length));
	}
	switch (toward) {		
	case 1:this->rotate = this->rotate_cur = PI / 2, dx = 0, dy = 1; break;
	case 2:this->rotate = this->rotate_cur = 0, dx = -1, dy = 0; break;
	case 3:this->rotate = this->rotate_cur = -PI / 2, dx = 0, dy = -1; break;
	case 4:this->rotate = this->rotate_cur = -PI, dx = 1, dy = 0; break;
	}
	this->pimg = trainpic1_head;
	for (i = 0; i < length; i++) {
		(this->boxes)[i].pimg = trainpic1_mid;
		(this->boxes)[i].rotate = this->rotate;
		(this->boxes)[i].rotate_cur = this->rotate_cur;
		(this->boxes)[i].toward = this->toward;
		(this->boxes)[i].x = this->x + dx;
		(this->boxes)[i].y = this->y + dy;
	}
	(this->boxes)[length - 1].pimg = waypic0;
}
int train::action(class cube*map[][12]) {
	int i;						//循环变量
	class cube*head_on=NULL;	//临时储存火车头部经过的铁轨
	int is_pass = 0;			//表示火车是否成功通过
	if (this->init_time > 0) {
		this->init_time--;
	}
	else {
		this->time+=this->speed;
		if (this->time % 50 + 1 == 50) {										//进入轨道处理
			if (this->boxes[length - 1].x > -1 && this->boxes[length - 1].x<12 && this->boxes[length - 1].y>-1 && this->boxes[length - 1].y < 12) {
				map[this->boxes[length - 1].y][this->boxes[length - 1].x]->add_train(-1);
			}
			for (i = this->length - 1; i > 0; i--) {
				this->boxes[i].x = this->boxes[i - 1].x;
				this->boxes[i].y = this->boxes[i - 1].y;
				
			}
			this->boxes[0].x = this->x; this->boxes[0].y = this->y;
			
			//火车方向变化
			for (i = this->length - 1; i > 0; i--) {
				this->boxes[i].toward = this->boxes[i - 1].toward;
			}
			if (this->x > -1 && this->x < 12 && this->y>-1 && this->y < 12) {
				this->boxes[0].toward = this->toward;
				head_on = map[this->y][this->x];
				if (this->toward == head_on->get_msg().in_type1) {
					switch (head_on->get_msg().trans_type1) {
					case -1:this->toward == 1 ? this->toward = 4 : this->toward -= 1; break;
					case 1: this->toward == 4 ? this->toward = 1 : this->toward += 1; break;
					}
				}
				else if (this->toward == head_on->get_msg().in_type2) {
					switch (head_on->get_msg().trans_type2) {
					case -1:this->toward == 1 ? this->toward = 4 : this->toward -= 1; break;
					case 1: this->toward == 4 ? this->toward = 1 : this->toward += 1; break;
					}
				}
			}
			//火车前进处理
			switch (this->toward) {
			case 1:this->y--; break;
			case 2:this->x++; break;
			case 3:this->y++; break;
			case 4:this->x--; break;
			}
			if (this->x > -1 && this->x < 12 && this->y>-1 && this->y < 12) {
				map[this->y][this->x]->add_train(1);
			}
			//以下为火车脱轨处理
			if (this->x > 0 && this->x < 11 && this->y>0 && this->y < 11) {
				head_on = map[this->y][this->x];
				if (head_on->get_msg().in_type1 == 5) {
				}
				else{
					if (this->toward == head_on->get_msg().in_type1) {
					}
					else if (this->toward == head_on->get_msg().in_type2) {
					}
					else {
						settarget(NULL);
						outway(this->x, this->y);					//脱轨动画
						//MessageBox(NULL, TEXT("火车脱轨"), TEXT("游戏失败"), MB_SETFOREGROUND);
						/*脱轨函数*/
						return 3;
					}
				}
				if (head_on->get_type() == 3) {
					switch (head_on->get_mode(-1)) {
					case 1:this->speed = 1; break;
					case 2:this->speed = 2; break;
					}
				}
			}
			else if ((this->x == 0 || this->x == 11 || this->y == 0 || this->y == 11) && (this->time > 50)) {
				head_on = map[this->y][this->x];
				if (this->fina != head_on->get_mode(-1)) {
					settarget(NULL);
					wrongouter(this->x, this->y,head_on->get_mode(-1));					//错误出口动画
					//MessageBox(NULL, TEXT("火车进入了错误轨道"), TEXT("游戏失败"), MB_SETFOREGROUND);
					/*错误出口函数*/
					return 5;
				}
				else {
					//火车成功通过
					is_pass = 1;
				}
			}

		}
		else if(this->time % 50 + 1 == 24) {							//轨道内处理
			//火车图片旋转相关
			for (i = this->length - 1; i > 0; i--) {
				this->boxes[i].is_turn = this->boxes[i - 1].is_turn;
				this->boxes[i].rotate = this->boxes[i - 1].rotate;
			}
			this->boxes[0].is_turn = this->is_turn;
			this->boxes[0].rotate = this->rotate;

			if (this->x > 0 && this->x < 11 && this->y>0 && this->y < 11) {
				head_on = map[this->y][this->x];
				if (head_on->get_msg().in_type1 == 5) {
					this->is_turn = 0;
				}
				else {
					if (this->toward == head_on->get_msg().in_type1) {
						switch (head_on->get_msg().trans_type1) {
						case -1:this->is_turn = 1; this->rotate += PI / 2; break;
						case 0:this->is_turn = 0; break;
						case 1:this->is_turn = 1; this->rotate -= PI / 2; break;
						}
					}
					else if (this->toward == head_on->get_msg().in_type2) {
						switch (head_on->get_msg().trans_type2) {
						case -1:this->is_turn = 1; this->rotate += PI / 2; break;
						case 0:this->is_turn = 0; break;
						case 1:this->is_turn = 1; this->rotate -= PI / 2; break;
						}
					}
				}
			}
		}
		else if (this->time % 50 + 1 == 34) {							//火车碰撞判断及处理
			if (this->x > -1 && this->x < 12 && this->y>-1 && this->y < 12) {
				if (map[this->y][this->x]->get_trainnum() > 1) {
					settarget(NULL);
					crash(this->x, this->y);					//火车相撞动画
					//MessageBox(NULL, TEXT("火车相撞"), TEXT("游戏失败"), MB_SETFOREGROUND);
					/*火车碰撞函数*/
					return 4;
				}
			}
		}

		if (this->is_turn==1) {						//火车图片旋转
			if (this->rotate_cur < this->rotate - 0.00001) {
				this->rotate_cur += this->speed*PI / 100;
			}
			if (this->rotate_cur > this->rotate + 0.00001) {
				this->rotate_cur -= this->speed*PI / 100;
			}
		}
		for (i = 0; i < this->length; i++) {
			if (this->boxes[i].is_turn == 1) {		//火车车厢图片旋转
				if (this->boxes[i].rotate_cur < this->boxes[i].rotate - 0.00001) {
					this->boxes[i].rotate_cur += this->speed*PI / 100;
				}
				if (this->boxes[i].rotate_cur > this->boxes[i].rotate + 0.00001) {
					this->boxes[i].rotate_cur -= this->speed*PI / 100;
				}
			}
		}


		this->draw();												//绘制火车图片
	}
	if (is_pass == 1) {
		return 8;
	}
	else {
		return 0;
	}
}
void train::delete_train() {
	if (this->boxes != NULL) {
		for (int i = 0; i < length; i++) {
			(this->boxes[i]).pimg = NULL;
		}
		free(this->boxes);
		this->boxes = NULL;
	}
	this->pimg = NULL;
}
void train::draw() {
	int i;							//循环变量
	int t = (this->time+1) % 50 ;	//计算时间偏移量
	int dx, dy;						//对应的x，y方向偏移量
	switch (this->toward) {
	case 1:dx = 0, dy = -1; break;
	case 2:dx = 1, dy = 0; break;
	case 3:dx = 0, dy = 1; break;
	case 4:dx = -1, dy = 0; break;
	}
	putimage_rotate(NULL, this->pimg, this->x * 50 + 25 + mapx + dx*(t - 49), this->y * 50 + 25 + mapy + dy*(t - 49), 0.5f, 0.5f, this->rotate_cur, 1);
	xyprintf(this->x * 50 + 25 + mapx + dx*(t - 49), this->y * 50 + 25 + mapy + dy*(t - 49), "%d", this->fina);
	for (i = 0; i < this->length; i++) {
		switch (this->boxes[i].toward) {
		case 1:dx = 0, dy = -1; break;
		case 2:dx = 1, dy = 0; break;
		case 3:dx = 0, dy = 1; break;
		case 4:dx = -1, dy = 0; break;
		}
		putimage_rotate(NULL, this->boxes[i].pimg, this->boxes[i].x * 50 + 25 + mapx + dx*(t - 49), this->boxes[i].y * 50 + 25 + mapy + dy*(t - 49), 0.5f, 0.5f, this->boxes[i].rotate_cur, 1);
	}
}