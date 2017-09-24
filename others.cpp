#include <graphics.h>
#include "levelmaker.h"
#include "para.h"

//根据鼠标坐标获取网格坐标
int getX(int x){
  return (x - 365) / 50;
}
int getY(int y){
  return (y - 10) / 50;
}
//判断鼠标是否在地图内
bool in_map(int x, int y){
  return !(x < 365 || x >= 965 || y < 10 || y >= 610);
}
//等待鼠标抬起动作
mouse_msg wait_up(){
  mouse_msg msg = {0};
  while (1) {
    msg = getmouse();
    if (msg.is_up())
      return msg;
  }
}
//计算ctrl.bind_num的值
void get_bind(){
  ctrl.bind_num = 1;
  while (1){
    int flag = 0;//记录是否有成员
    for (int i = 0; i < MAP_HEIGHT; i++){
      for (int j = 0; j < MAP_WIDTH; j++){
        if (map[i][j].bind_num == ctrl.bind_num){
          j = MAP_WIDTH;
          i = MAP_HEIGHT;
          flag = 1;
        }
      }
    }
    if (flag)
      ctrl.bind_num++;
    else
      break;
  }
}

int to_int(char * str, int len){
  int result = 0;
  for (int i = 0; i < len; i++){
    if (str[i] >= '0' && str[i] <= '9'){
      result *= 10;
      result += str[i] - '0';
    } else {
      return result;
    }
  }
  return result;
}
