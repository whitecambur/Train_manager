#pragma once
#define mapx 240			//��Ϸ��ͼ��x����
#define mapy 20				//��Ϸ��ͼ��y����
#include"draw.h"
struct train_way {
	int in_type1;					//�������1
	int trans_type1;				//�����������1
	int in_type2;					//�������2
	int trans_type2;				//�����������2
};
class cube{							//�����
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
	int type;						//������
	struct train_way the_way;		//�������������
	PIMAGE pimg;					//�����Ӧ��ͼƬ(ָ��)
	PIMAGE sign;						//�����Ӧ�ı�ʶ
	double rotate;					//ͼƬ��ת�Ƕ�
	int train_num;					//����ϵĻ���Ŀ
};
class empty_cube :public cube {		//�չ��
public:
	int get_mode(int num) { return 0; };
};
class normal_cube :public cube{		//��׼���
public:
	int get_mode(int num);
private:
	int enter_num;
};
class changable_cube :public cube{	//�ɱ���
public:
	int get_mode(int trans_way);
	void press(int type, class cube *map[][12]);
	void draw(int x,int y,int alpha);
private:
	int trans_way;
	double rotate_cur;					//ͼƬ��ת��ǰ�Ƕ�
	int trans_team;							//���������������
};
class speed_cube :public cube {		//���ٹ��
public:
	int get_mode(int speedtype);
private:
	int speedtype;
};
struct train_box {
	int x;					//��������x����
	int y;					//��������y����
	int toward;				//���᷽��
	int is_turn;			//�����Ƿ�ת��
	double rotate;			//����ͼƬת��
	double rotate_cur;		//����ͼƬ��ǰת��
	PIMAGE pimg;			//����ͼƬ
};
class train {
public:
	void creat(int x,int y,int length,int speed,int fina,int init_time);	//���ɻ�
	int action(class cube *map[][12]);			//�𳵶���
	void delete_train();					//ɾ����
private:
	void draw();			//�𳵻�ͼ����
	int init_time;			//�𳵳���ʱ��
	int time;				//���ڲ���ʱ��
	bool is_turn;			//����Ƿ�����ת��
	int x;					//������x����
	int y;					//������y����
	int length;				//�𳵳���
	struct train_box *boxes;//�𳵳���
	int speed;				//���ٶ�
	int toward;				//�𳵷���
	bool is_finished;		//���Ƿ񵽴��յ�
	double rotate;				//��ͼƬĿ��Ƕ�
	double rotate_cur;			//��ͼƬ��ǰ�Ƕ�
	int fina;				//��Ŀ���յ�
	PIMAGE pimg;				//��ͼƬ
};

int load_pic();			//��ȡͼƬ