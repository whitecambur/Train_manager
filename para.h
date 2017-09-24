#ifndef PARA_H_
#define PARA_H_

#include "mine_btn.h"
#include "levelmaker.h"

//外部变量声明
extern MapCube map[][MAP_WIDTH];
extern Control ctrl;
extern Train trains[20];
extern PIMAGE img_1;
extern PIMAGE img_2;
extern PIMAGE img_3;
extern PIMAGE img_4;
extern PIMAGE img_5;
extern PIMAGE img_6;
extern PIMAGE img_7;
extern PIMAGE img_8;
extern PIMAGE img_9;
extern PIMAGE img_blank;//空地图片
extern PIMAGE img_blank45170;
extern PIMAGE img_track1;//竖直方向直道
extern PIMAGE img_track2;//第一象限弯道
extern PIMAGE img_track3;//四向轨道
extern PIMAGE img_rotate1;//旋转轨道标识
extern PIMAGE img_rotate2;//旋转轨道标识
extern PIMAGE img_rotate3;//旋转轨道标识
extern PIMAGE img_acc1;//加速轨道标识
extern PIMAGE img_acc2;//加速轨道标识
extern PIMAGE img_boom;//爆炸轨道标识
extern PIMAGE img_btn_add_track;//增加轨道按钮
extern PIMAGE img_btn_add_rotate;//增加旋转标识按钮
extern PIMAGE img_btn_add_acc;//增加加速标识按钮
extern PIMAGE img_btn_add_boom;//增加爆炸标识按钮
extern PIMAGE img_btn_clear;//清屏按钮
extern PIMAGE img_btn_save;//结束按钮
extern PIMAGE img_btn_left_a;//左箭头
extern PIMAGE img_btn_right_a;//右箭头
extern PIMAGE img_btn_enterxy;//
extern PIMAGE img_btn_outerxy;//
extern PIMAGE img_btn_showtime;//
extern PIMAGE img_btn_speed;//
extern PIMAGE img_btn_length;//
extern PIMAGE img_btn_back;//返回按钮
extern BTN btn_add_track;
extern BTN btn_add_rotate;
extern BTN btn_add_acc;
extern BTN btn_add_boom;
extern BTN btn_add_bind;
extern BTN btn_add_station;
extern BTN btn_left_a;
extern BTN btn_right_a;
extern BTN btn_enterxy;
extern BTN btn_outerxy;
extern BTN btn_showtime;
extern BTN btn_speed;
extern BTN btn_length;
extern BTN btn_back;

#endif
