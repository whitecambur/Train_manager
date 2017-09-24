#ifndef MINE_BTN_H_
#define MINE_BTN_H_

#include <graphics.h>

//void nothing_happened();
//#define BTN_NH nothing_happened;//定义无事件函数
void BTN_NH();

class BTN{
private:
  int m_x1;//左上端点x坐标
  int m_y1;//左上端点y坐标
  int m_x2;//右下端点x坐标
  int m_y2;//右下端点y坐标
  int m_length;//按钮竖直方向长度
  int m_width;//按钮水平方向长度
  PIMAGE m_img;//按钮图像

  void (*m_function_left)();//鼠标左键操作
  void (*m_function_right)();//鼠标右键操作
  void (*m_function_hover)();//鼠标悬空操作
  void (*m_function_hoverback)();//鼠标离开操作
  void (*m_function_down)();//鼠标按下操作
  void (*m_function_up)();//鼠标抬起操作

  bool m_is_disabled;//按钮是否失效。0为否

  int m_is_highlight;//按钮是否高亮 0为普通 1为高亮 -1为选中(变暗)

  //bool m_createmode;//创建按钮的方式。
            //0代表按照左上端点和右下端点坐标创建。
            //1代表按照左上端点坐标和长宽创建
public:
  BTN(
  int x1 = 0,//按钮左上端点x坐标
  int y1 = 0,//按钮左上端点y坐标
  int x2 = 100,//按钮右上端点x坐标
  int y2 = 100,//按钮右上端点y坐标

  PIMAGE img = NULL,//默认无填充图片

  void (*function_left)() = BTN_NH,//左键事件
  void (*function_right)() = BTN_NH,//右键事件
  void (*function_hover)() = BTN_NH,//悬空事件
  void (*function_hoverback)() = BTN_NH,//离开事件
  void (*function_down)() = BTN_NH,//按下事件
  void (*function_up)() = BTN_NH,//抬起事件
  
  bool is_disabled = 0//是否失灵。默认为否
  );//两个端点的按钮构造函数
  
  BTN(
  bool createmode = 1,//使用按钮左上端点坐标和长宽来创建按钮

  int x = 0,//按钮左上端点x坐标
  int y = 0,//按钮左上端点y坐标
  int width = 100,//按钮宽度
  int length = 100,//按钮长度

  PIMAGE img = NULL,//按钮图片

  void (*function_left)() = BTN_NH,//左键事件
  void (*function_right)() = BTN_NH,//右键事件
  void (*function_hover)() = BTN_NH,//悬浮事件
  void (*function_hoverback)() = BTN_NH,//离开事件
  void (*function_down)() = BTN_NH,//按下事件
  void (*function_up)() = BTN_NH,//抬起事件
  
  bool is_disabled = 0//默认没有失效
  );//左上端点坐标和长宽创建按钮的构造函数

  ~BTN();//析构函数

  //以下函数可以获得按钮属性
  int get_x1(){return m_x1;}
  int get_y1(){return m_y1;}
  int get_x2(){return m_x2;}
  int get_y2(){return m_y2;}
  int get_length(){return m_length;}
  int get_width(){return m_width;}
  PIMAGE get_img(){return m_img;}
  bool get_is_disabled(){return m_is_disabled;}
  int get_is_highlight(){return m_is_highlight;}
  void (*get_function_left())(){return m_function_left;}
  void (*get_function_right())(){return m_function_right;}
  void (*get_function_hover())(){return m_function_hover;}
  void (*get_function_hoverback())(){return m_function_hoverback;}
  void (*get_function_down())(){return m_function_down;}
  void (*get_function_up())(){return m_function_up;}

  //鼠标操作
  bool left(int mouse_x,int mouse_y);
  bool right(int mouse_x,int mouse_y);
  bool hover(int mouse_x,int mouse_y);
  bool hoverback(int mouse_x,int mouse_y);
  bool down(int mouse_x,int mouse_y);
  bool up(int mouse_x,int mouse_y);

  //改变按钮属性的函数
  bool set_x1(int new_x1);
  bool set_y1(int new_y1);
  bool set_x2(int new_x2);
  bool set_y2(int new_y2);
  bool set_img(PIMAGE new_image);
  bool set_disabled(bool is_disabled);//设置按钮为指定状态
  bool change_disabled();//切换按钮失效状态
  bool set_highlight(int is_highlight);
  bool set_function_left(void (*new_function_left)());
  bool set_function_right(void (*new_function_right)());
  bool set_function_hover(void (*new_function_hover)());
  bool set_function_hoverback(void (*new_function_hoverback)());
  bool set_function_down(void (*new_function_down)());
  bool set_function_up(void (*new_function_up)());

  void show();//显示按钮
};

#endif
