#pragma once
#define mapx 240			//游戏地图的x坐标
#define mapy 20				//游戏地图的y坐标
#include"draw.h"
struct train_way {
	int in_type1;					//入口类型1
	int trans_type1;				//运行情况类型1
	int in_type2;					//入口类型2
	int trans_type2;				//运行情况类型2
};
class cube{							//基轨道
public:
	void create(int pic_type,int type);
	virtual int get_mode(int) = 0;
	virtual void press(int type, class cube *map[][12]) {};
	void delete_cube();
	int get_type();
	void add_train(int num);
	int get_trainnum();
	struct train_way get_msg();
	virtual void draw(int x,int y,int alpha);
protected:
	int type;						//轨道类别
	struct train_way the_way;		//轨道进出口属性
	PIMAGE pimg;					//轨道对应的图片(指针)
	PIMAGE sign;						//轨道对应的标识
	double rotate;					//图片旋转角度
	int train_num;					//轨道上的火车数目
};
class empty_cube :public cube {		//空轨道
public:
	int get_mode(int num) { return 0; };
};
class normal_cube :public cube{		//标准轨道
public:
	int get_mode(int num);
private:
	int enter_num;
};
class changable_cube :public cube{	//可变轨道
public:
	int get_mode(int trans_way);
	void press(int type, class cube *map[][12]);
	void draw(int x,int y,int alpha);
private:
	int trans_way;
	double rotate_cur;					//图片旋转当前角度
	int trans_team;							//所属的联动轨道组
};
class speed_cube :public cube {		//增速轨道
public:
	int get_mode(int speedtype);
private:
	int speedtype;
};
struct train_box {
	int x;					//车厢中心x坐标
	int y;					//车厢中心y坐标
	int toward;				//车厢方向
	int is_turn;			//车箱是否转弯
	double rotate;			//车厢图片转角
	double rotate_cur;		//车厢图片当前转角
	PIMAGE pimg;			//车厢图片
};
class train {
public:
	void creat(int x,int y,int length,int speed,int fina,int init_time);	//生成火车
	int action(class cube *map[][12]);			//火车动作
	void delete_train();					//删除火车
private:
	void draw();			//火车绘图函数
	int init_time;			//火车出现时间
	int time;				//火车内部计时器
	bool is_turn;			//火炽是否正在转弯
	int x;					//火车中心x坐标
	int y;					//火车中心y坐标
	int length;				//火车长度
	struct train_box *boxes;//火车车厢
	int speed;				//火车速度
	int toward;				//火车方向
	bool is_finished;		//火车是否到达终点
	double rotate;				//火车图片目标角度
	double rotate_cur;			//火车图片当前角度
	int fina;				//火车目标终点
	PIMAGE pimg;				//火车图片
};

int load_pic();			//读取图片