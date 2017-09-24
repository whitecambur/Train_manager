#ifndef MINE_BTN_H_
#define MINE_BTN_H_

#include <graphics.h>

//void nothing_happened();
//#define BTN_NH nothing_happened;//�������¼�����
void BTN_NH();

class BTN{
private:
  int m_x1;//���϶˵�x����
  int m_y1;//���϶˵�y����
  int m_x2;//���¶˵�x����
  int m_y2;//���¶˵�y����
  int m_length;//��ť��ֱ���򳤶�
  int m_width;//��ťˮƽ���򳤶�
  PIMAGE m_img;//��ťͼ��

  void (*m_function_left)();//����������
  void (*m_function_right)();//����Ҽ�����
  void (*m_function_hover)();//������ղ���
  void (*m_function_hoverback)();//����뿪����
  void (*m_function_down)();//��갴�²���
  void (*m_function_up)();//���̧�����

  bool m_is_disabled;//��ť�Ƿ�ʧЧ��0Ϊ��

  int m_is_highlight;//��ť�Ƿ���� 0Ϊ��ͨ 1Ϊ���� -1Ϊѡ��(�䰵)

  //bool m_createmode;//������ť�ķ�ʽ��
            //0���������϶˵�����¶˵����괴����
            //1���������϶˵�����ͳ�����
public:
  BTN(
  int x1 = 0,//��ť���϶˵�x����
  int y1 = 0,//��ť���϶˵�y����
  int x2 = 100,//��ť���϶˵�x����
  int y2 = 100,//��ť���϶˵�y����

  PIMAGE img = NULL,//Ĭ�������ͼƬ

  void (*function_left)() = BTN_NH,//����¼�
  void (*function_right)() = BTN_NH,//�Ҽ��¼�
  void (*function_hover)() = BTN_NH,//�����¼�
  void (*function_hoverback)() = BTN_NH,//�뿪�¼�
  void (*function_down)() = BTN_NH,//�����¼�
  void (*function_up)() = BTN_NH,//̧���¼�
  
  bool is_disabled = 0//�Ƿ�ʧ�顣Ĭ��Ϊ��
  );//�����˵�İ�ť���캯��
  
  BTN(
  bool createmode = 1,//ʹ�ð�ť���϶˵�����ͳ�����������ť

  int x = 0,//��ť���϶˵�x����
  int y = 0,//��ť���϶˵�y����
  int width = 100,//��ť���
  int length = 100,//��ť����

  PIMAGE img = NULL,//��ťͼƬ

  void (*function_left)() = BTN_NH,//����¼�
  void (*function_right)() = BTN_NH,//�Ҽ��¼�
  void (*function_hover)() = BTN_NH,//�����¼�
  void (*function_hoverback)() = BTN_NH,//�뿪�¼�
  void (*function_down)() = BTN_NH,//�����¼�
  void (*function_up)() = BTN_NH,//̧���¼�
  
  bool is_disabled = 0//Ĭ��û��ʧЧ
  );//���϶˵�����ͳ�������ť�Ĺ��캯��

  ~BTN();//��������

  //���º������Ի�ð�ť����
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

  //������
  bool left(int mouse_x,int mouse_y);
  bool right(int mouse_x,int mouse_y);
  bool hover(int mouse_x,int mouse_y);
  bool hoverback(int mouse_x,int mouse_y);
  bool down(int mouse_x,int mouse_y);
  bool up(int mouse_x,int mouse_y);

  //�ı䰴ť���Եĺ���
  bool set_x1(int new_x1);
  bool set_y1(int new_y1);
  bool set_x2(int new_x2);
  bool set_y2(int new_y2);
  bool set_img(PIMAGE new_image);
  bool set_disabled(bool is_disabled);//���ð�ťΪָ��״̬
  bool change_disabled();//�л���ťʧЧ״̬
  bool set_highlight(int is_highlight);
  bool set_function_left(void (*new_function_left)());
  bool set_function_right(void (*new_function_right)());
  bool set_function_hover(void (*new_function_hover)());
  bool set_function_hoverback(void (*new_function_hoverback)());
  bool set_function_down(void (*new_function_down)());
  bool set_function_up(void (*new_function_up)());

  void show();//��ʾ��ť
};

#endif
