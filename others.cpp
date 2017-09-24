#include <graphics.h>
#include "levelmaker.h"
#include "para.h"

//������������ȡ��������
int getX(int x){
  return (x - 365) / 50;
}
int getY(int y){
  return (y - 10) / 50;
}
//�ж�����Ƿ��ڵ�ͼ��
bool in_map(int x, int y){
  return !(x < 365 || x >= 965 || y < 10 || y >= 610);
}
//�ȴ����̧����
mouse_msg wait_up(){
  mouse_msg msg = {0};
  while (1) {
    msg = getmouse();
    if (msg.is_up())
      return msg;
  }
}
//����ctrl.bind_num��ֵ
void get_bind(){
  ctrl.bind_num = 1;
  while (1){
    int flag = 0;//��¼�Ƿ��г�Ա
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
