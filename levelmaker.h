#ifndef LEVEL_MAKER_H_
#define LEVEL_MAKER_H_

#define MAP_WIDTH 12
#define MAP_HEIGHT 12

struct MapCube {
  int type;//轨道类型 0为空地 1为水平方向直道 2为第一象限弯道 3为四向轨道
  int rotate;//轨道顺时针旋转角度/90
             //如 0为不旋转 1为旋转90度
             //可变轨道的旋转动作可以直接操作此值
  int child_type;//0为普通 1为可变 2为变速 3为炸弹 4为口
  bool speed_type;//变速轨道的类型 0加速 其他减速
  int rotate_type;//可变轨道的类型 1为顺时针 -1为逆时针 0为360度
  int time1;//炸弹轨道中对应的炸弹爆炸时间
  int time2;//炸弹轨道中对应的炸弹拆除时间
  int bind_num;//联动组序号
  int train_code;//以此为口的火车编号 默认为0 代表没有
  bool station_type;//0为出口 1为入口
};

struct Control {
  int add_track;//增加铁轨按钮状态 1为竖直方向直道 2为第一象限弯道 3为四向轨道
  int add_rotate_type;//可变铁轨的类型 1为顺时针 -1为逆时针 0为360
  bool acc_type;//变速按钮的类型 0为加速 1为减速
  int bind_num;//联动组的最大序号
  bool qedit;//快速编辑模式
  int train_code;//当前选中的火车编号 1<20
};

struct Train {
  int code;//火车编号 范围1~20
  int enter[2];//入口坐标 [-2, -2]代表不存在
  int outer[2];//出口坐标 [-2, -2]代表不存在
  int showtime;//出现时间 1<9999
  bool speed;//速度 0为慢 1为快
  int length;//长度 1<50
};

#endif
