#ifndef LEVEL_MAKER_H_
#define LEVEL_MAKER_H_

#define MAP_WIDTH 12
#define MAP_HEIGHT 12

struct MapCube {
  int type;//������� 0Ϊ�յ� 1Ϊˮƽ����ֱ�� 2Ϊ��һ������� 3Ϊ������
  int rotate;//���˳ʱ����ת�Ƕ�/90
             //�� 0Ϊ����ת 1Ϊ��ת90��
             //�ɱ�������ת��������ֱ�Ӳ�����ֵ
  int child_type;//0Ϊ��ͨ 1Ϊ�ɱ� 2Ϊ���� 3Ϊը�� 4Ϊ��
  bool speed_type;//���ٹ�������� 0���� ��������
  int rotate_type;//�ɱ��������� 1Ϊ˳ʱ�� -1Ϊ��ʱ�� 0Ϊ360��
  int time1;//ը������ж�Ӧ��ը����ըʱ��
  int time2;//ը������ж�Ӧ��ը�����ʱ��
  int bind_num;//���������
  int train_code;//�Դ�Ϊ�ڵĻ𳵱�� Ĭ��Ϊ0 ����û��
  bool station_type;//0Ϊ���� 1Ϊ���
};

struct Control {
  int add_track;//�������찴ť״̬ 1Ϊ��ֱ����ֱ�� 2Ϊ��һ������� 3Ϊ������
  int add_rotate_type;//�ɱ���������� 1Ϊ˳ʱ�� -1Ϊ��ʱ�� 0Ϊ360
  bool acc_type;//���ٰ�ť������ 0Ϊ���� 1Ϊ����
  int bind_num;//�������������
  bool qedit;//���ٱ༭ģʽ
  int train_code;//��ǰѡ�еĻ𳵱�� 1<20
};

struct Train {
  int code;//�𳵱�� ��Χ1~20
  int enter[2];//������� [-2, -2]��������
  int outer[2];//�������� [-2, -2]��������
  int showtime;//����ʱ�� 1<9999
  bool speed;//�ٶ� 0Ϊ�� 1Ϊ��
  int length;//���� 1<50
};

#endif
