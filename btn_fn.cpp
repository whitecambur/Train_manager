#include <graphics.h>
#include <cstring>
#include <string>
#include <fstream>
#include "mine_btn.h"
#include "levelmaker.h"//�ṹ���� ��������
#include "others.h"
#include "para.h"//�ⲿ��������
#include "trainmaker.h"

//�����ⲿ����
void print_screen();
void init_map();
void init_trains();

//���ļ��ڵĺ�������
void print_screen_bind();
void routine(BTN&, void (*)(int, int), void (*)());
void btnf_add_track_inroutine(int, int);
void btnf_add_rotate_inroutine(int, int);
void btnf_add_acc_inroutine(int, int);
void btnf_add_boom_inroutine(int, int);
void btnf_add_station_inroutine(int, int);
void btnf_get_enterxy_inroutine(int, int);
void btnf_get_outerxy_inroutine(int, int);

//////////////////////////����
void btnf_add_track(){
  routine(btn_add_track, btnf_add_track_inroutine, print_screen);
}
void btnf_change_track(){
  ctrl.add_track = ctrl.add_track % 3 + 1;

  switch (ctrl.add_track) {
    case 1:
      putimage(img_btn_add_track, 80, 10, img_track1);
      break;
    case 2:
      putimage(img_btn_add_track, 80, 10, img_track2);
      break;
    case 3:
      putimage(img_btn_add_track, 80, 10, img_track3);
      break;
  }
  btn_add_track.set_img(img_btn_add_track);
}
void btnf_add_rotate(){
  routine(btn_add_rotate, btnf_add_rotate_inroutine, print_screen);
}
void btnf_change_rotate(){
  ctrl.add_rotate_type = (ctrl.add_rotate_type + 2) % 3 - 1;
  if (ctrl.add_rotate_type == 1)
    putimage(img_btn_add_rotate, 80, 10, img_rotate1);
  else if (ctrl.add_rotate_type == -1)
    putimage(img_btn_add_rotate, 80, 10, img_rotate2);
  else if (!ctrl.add_rotate_type)
    putimage(img_btn_add_rotate, 80, 10, img_rotate3);
  btn_add_rotate.set_img(img_btn_add_rotate);
}
void btnf_add_acc(){
  routine(btn_add_acc, btnf_add_acc_inroutine, print_screen);
}
void btnf_change_acc(){
  ctrl.acc_type = !ctrl.acc_type;
  if (!ctrl.acc_type)
    putimage(img_btn_add_acc, 80, 10, img_acc1);
  else
    putimage(img_btn_add_acc, 80, 10, img_acc2);
}
void btnf_add_boom(){
  routine(btn_add_boom, btnf_add_boom_inroutine, print_screen);
}

void btnf_get_enterxy(){
  routine(btn_enterxy, btnf_get_enterxy_inroutine, print_screen_train);
}
void btnf_get_outerxy(){
  routine(btn_outerxy, btnf_get_outerxy_inroutine, print_screen_train);
}

void btnf_reset_enterxy() {
	trains[ctrl.train_code - 1].enter[0] = trains[ctrl.train_code - 1].enter[1] = -2;
}
void btnf_reset_outerxy() {
	trains[ctrl.train_code - 1].outer[0] = trains[ctrl.train_code - 1].outer[1] = -2;
}
/***************
�����ͼ
*****************/
void btnf_save(){
  //���û�б༭�κλ���ؿ���Ч
  int flag = 0;//Ŀǰ�༭��0����
  for (int i = 0; i < 20 && !flag; i++){
    if (trains[i].enter[0] != -2 && trains[i].outer[0] != -2)
      flag++;
  }
  if (!flag){
    MessageBox(NULL,TEXT("�����ٱ༭һ����"),TEXT("�ؿ���Ч"),MB_SETFOREGROUND);
    return;
  }
  
  using namespace std;

	char name[45];//��¼�����к�׺���ļ���
	char whole_name[60] = "addons//";
  int station_code = 1;
  int stationxy[40][2];//��¼�ڵ�����

  if (inputbox_getline("�����ͼ", "��Ϊ��ͼ����(������20���ַ�)", name, 20)) {
    ofstream fout;
		//��д�ؿ��༭���ļ�
		strcat(whole_name, name);
		strcat(whole_name, ".lm");//��׺Ϊ.levelmaker
		fout.open(whole_name);
		for (int i = 0; i < MAP_HEIGHT; i++) {
      for (int j = 0; j < MAP_WIDTH; j++) {
        fout << "type:" << map[i][j].type << endl;
        if (!map[i][j].type) continue;
        fout << "rotate:" << map[i][j].rotate << endl
             << "child_type:" << map[i][j].child_type << endl
						 << "speed_type:" << (int)map[i][j].speed_type << endl
						 << "rotate_type:" << map[i][j].rotate_type << endl
						 << "bind_num:" << map[i][j].bind_num << endl
						 << "train_code:" << map[i][j].train_code << endl
						 << "station_type:" << (int)map[i][j].station_type << endl;
      }
		}
		fout << endl;
		for (int i = 0; i < 20; i++){
			if (trains[i].enter[0] != -2 && trains[i].enter[1] != -2 && trains[i].outer[0] != -2 && trains[i].outer[1] != -2){
				fout << "enter:" << trains[i].enter[0] << "," << trains[i].enter[1] << endl
						 << "outer:" << trains[i].outer[0] << "," << trains[i].outer[1] << endl
						 << "showtime:" << trains[i].showtime << endl
						 << "speed:" << (int)trains[i].speed << endl
						 << "length:" << trains[i].length << endl;
			}
		}
		fout.close();

    //дtxt�ļ�
    strcpy(whole_name, "addons//");
		strcat(whole_name, name);
    strcat(whole_name, ".txt");
    fout.open(whole_name);
    for (int i = 0; i < MAP_HEIGHT; i++) {
      for (int j = 0; j < MAP_WIDTH; j++) {
        MapCube temp = map[i][j];
        
        fout << "type:";
        if (!temp.type){//����ǿյ�
					fout << "0\n";
					continue;
        } else {
          //������ǿյ�
          switch (temp.child_type){
            case 0:
              //��ͨ����
              fout << "1\n";
              break;
            case 1:
              if (!temp.bind_num){
                //�������Ϊ0
                fout << "2\n";
              } else {
                //��������
                fout << "5\n";
              }
              break;
            case 2:
              //����
              fout << "3\n";
              break;
            case 3:
              //ը��
              fout << "4\n";
              break;
            case 4:
              //��
              fout << "6\n";
              break;
          }
        }
        
        fout << "shape:";
        if (temp.type == 1 && temp.rotate % 2 == 1){
          //��ֱֱ��
          fout << "1\n";
        }
        else if (temp.type == 1 && temp.rotate % 2 == 0){
          //ˮƽֱ��
          fout << "2\n";
        }
        else if (temp.type == 2){
          //���
          fout << 3 + (4 - temp.rotate) % 4<< endl;
        } else {
          //����
          fout << "7\n";
        }
        
        if (temp.child_type == 1){
          //�ɱ�������ת��ʽ
          fout << "trans_way:" << temp.rotate_type << endl;
        }

        if (temp.bind_num){
          //�����������
          fout << "connection:" << temp.bind_num << endl;
        }

        if (temp.child_type == 2){
          //��������ı��ٷ�ʽ
          fout << "speed_way:" << temp.speed_type << endl;
        }

        if (temp.child_type == 4){
          //�ڵ����
          fout << "station_code:" << station_code++ << endl;
          stationxy[station_code - 2][0] = j;
          stationxy[station_code - 2][1] = i;
        }
      }
    }

    fout << endl;
    station_code = 1;

    //�������Ϣ
    for (int i = 0; i < 20; i++){
      if (trains[i].enter[0] != -2 && trains[i].outer[0] != -2){
        //�������Ϣ
        fout << "enter:";
        if (!trains[i].enter[0]){
          fout << "-1,";
        } else if (trains[i].enter[0] == MAP_WIDTH - 1){
          fout << MAP_WIDTH << ",";
        } else {
          fout << trains[i].enter[0] << ",";
        }
        if (!trains[i].enter[1]){
          fout << "-1\n";
        } else if (trains[i].enter[1] == MAP_HEIGHT - 1){
          fout << MAP_HEIGHT << endl;
        } else {
          fout << trains[i].enter[1] << endl;
        }

        fout << "outer:";
        for (int j = 0; j < 40; j++){
          if (stationxy[j][0] == trains[i].outer[0] && stationxy[j][1] == trains[i].outer[1]){
            fout << j + 1 << endl;
            break;
          }
        }

        fout << "showtime:" << trains[i].showtime << endl;

        fout << "speed:" << trains[i].speed << endl;
        fout << "length:" << trains[i].length << endl;
      }
    }

    fout.close();

    //�ѹؿ���д��level_list�ļ���
    //�ļ���Ϊtrain_manager.ll
    //���ж�addons���Ƿ��Ѿ����ڴ��ļ�
    ifstream fin;
    string str;
    bool flag = 0;//��¼�Ƿ������ͬ���ؿ�
    fin.open("addons//train_manager.ll");
    getline(fin, str);
    while (str.length()){
      if (flag = str == name){
        break;
      }
      getline(fin, str);
    }
    fin.close();
    if (!flag){//������ͬ���ؿ�
      fout.open("addons//train_manager.ll", ios_base::app | ios_base::out);
      fout << name << endl;
      fout.close();
    }
  }
}
/****************
��ȡ��ͼ
*****************/
void btnf_load(){
  using namespace std;
  char whole_name[60] = "addons//";
  char name[45];
  if (inputbox_getline("��ȡ��ͼ", "��������Ҫ��ȡ�ĵ�ͼ��(������20���ַ�)", name, 20)) {
    strcat(name, ".lm");
    strcat(whole_name, name);
    ifstream fin;
    fin.open(whole_name);
    if (fin.is_open()) {
      //�����ԭ���ĵ�ͼ����
			init_map();
			init_trains();
      //�����ļ��е��ַ���
      string str;
      for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
          getline(fin, str);
          map[i][j].type = str[str.length() - 1] - '0';//ȡ���һλ
          if (map[i][j].type) {
            getline(fin, str);
            map[i][j].rotate = str[str.length() - 1] - '0';
            getline(fin, str);
            map[i][j].child_type = str[str.length() - 1] - '0';
            getline(fin, str);
						map[i][j].speed_type = str[str.length() - 1] - '0';
						getline(fin, str);
						map[i][j].rotate_type = str[str.length() - 1] - '0';
						if (str.length() == 14)
							map[i][j].rotate_type = -1;
						getline(fin, str);
						map[i][j].bind_num = str[str.length() - 1] - '0';
						getline(fin, str);
						if (str[str.length() - 2] != ':'){
							//�������λ��
							map[i][j].train_code = (str[str.length() - 2] - '0') * 10 + str[str.length() - 1] - '0';
						} else 
							map[i][j].train_code = str[str.length() - 1] - '0';
						getline(fin, str);
						map[i][j].station_type = str[str.length() - 1] - '0';
          }
        }
			}
			getline(fin, str);//��ȡ����
			for (int i = 0; i < 20; i++){
				//��ȡ����Ϣ
				getline(fin, str);
				if (!str.length())
					break;
				if (str[7] != ','){
					//����������λ��
					trains[i].enter[0] = (str[6] - '0') * 10 + str[7] - '0';
				} else {
					trains[i].enter[0] = str[6] - '0';
				}
				if (str[str.length() - 2] != ','){
					//����������λ��
					trains[i].enter[1] = (str[str.length() - 2] - '0') * 10 + str[str.length() - 1] - '0';
				} else {
					trains[i].enter[1] = str[str.length() - 1] - '0';
				}

				getline(fin, str);
				if (str[7] != ','){
					//����������λ��
					trains[i].outer[0] = (str[6] - '0') * 10 + str[7] - '0';
				} else {
					trains[i].outer[0] = str[6] - '0';
				}
				if (str[str.length() - 2] != ','){
					//����������λ��
					trains[i].outer[1] = (str[str.length() - 2] - '0') * 10 + str[str.length() - 1] - '0';
				} else {
					trains[i].outer[1] = str[str.length() - 1] - '0';
				}

				getline(fin, str);
				trains[i].showtime = 0;
				for (int j = 9; str[j] >= '0' && str[j] <= '9'; j++){
					trains[i].showtime *= 10;
					trains[i].showtime += str[j] - '0';
				}

				getline(fin, str);
				trains[i].speed = str[str.length() - 1] - '0';

				getline(fin, str);
				if (str[str.length() - 2] != ':'){
					//��λ��
					trains[i].length = (str[str.length() - 2] - '0') * 10 + str[str.length() - 1] - '0';
				} else {
					trains[i].length = str[str.length() - 1] - '0';
				}
			}
    }
  }
}

/*************
�������
**************/
void btnf_add_bind(){
  btn_add_bind.set_highlight(-1);

  btn_add_bind.show();

  mouse_msg msg = {0};
  for (; is_run(); delay_fps(60)){
    while (mousemsg()){
      msg = getmouse();
      if (msg.is_right()){
        //�Ҽ�ȡ������
        wait_up();
        return;
      }
      else if (msg.is_left()){
        if (!in_map(msg.x, msg.y)){
          //��겻�������ϰ��µ����
          wait_up();
        }
        else {
          //�������������
          int x1, y1;//��������1
          x1 = getX(msg.x);
          y1 = getY(msg.y);
          if (!map[y1][x1].bind_num && map[y1][x1].child_type == 1 && ctrl.bind_num <= 9){
            //����������û����  ����ɱ� �� ����������9
            msg = wait_up();
            if (in_map(msg.x, msg.y)){
              int x2, y2;
              x2 = getX(msg.x);
              y2 = getY(msg.y);
              if (x1 == x2 && y1 == y2){
                //��ͬһ������̧��
                map[y1][x1].bind_num = ctrl.bind_num;
                //�ҵ�Ŀǰû�г�Ա����С�����
                get_bind();
              }
            }
          } else if (map[y1][x1].bind_num){
            //�����������
            int flag = 1;//�Ƿ����
            for (; is_run() && flag; delay_fps(60)){
              print_screen_bind();//ˢ��
              //��ͼ
              switch (map[y1][x1].bind_num){
                case 1:
                  putimage_transparent(NULL, img_1, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 2:
                  putimage_transparent(NULL, img_2, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 3:
                  putimage_transparent(NULL, img_3, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 4:
                  putimage_transparent(NULL, img_4, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 5:
                  putimage_transparent(NULL, img_5, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 6:
                  putimage_transparent(NULL, img_6, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 7:
                  putimage_transparent(NULL, img_7, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 8:
                  putimage_transparent(NULL, img_8, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
                case 9:
                  putimage_transparent(NULL, img_9, msg.x - 25, msg.y - 25, EGERGB(255, 255, 255));
                  break;
              }
              while (mousemsg()){
                msg = getmouse();
                if (msg.is_up()){
                  //���̧��
                  int x2, y2;
                  if (!in_map(msg.x, msg.y))
                    flag = 0;
                  x2 = getX(msg.x);
                  y2 = getY(msg.y);
                  if (x1 == x2 && y1 == y2){
                    //ͬһ������
                    map[y1][x1].bind_num = 0;
                    get_bind();
                    flag = 0;
                  } else if (!map[y2][x2].bind_num && map[y2][x2].child_type == 1){
                    //��ͬ������û�б���ҿɱ�
                    map[y2][x2].bind_num = map[y1][x1].bind_num;
                    flag = 0;
                  } else {
                    flag = 0;
                  }
                }
              }
            }
          }
        }
      }
    }
    print_screen_bind();
  }
}

void btnf_add_station(){
  routine(btn_add_station, btnf_add_station_inroutine, print_screen);
}

/****************
��������ˢ��
****************/
void print_screen_bind(){
  PIMAGE temp = newimage(50, 50);
  setfillcolor(WHITE, temp);
  bar(0, 0, 50, 50, temp);
  print_screen();
  for (int i = 0; i < MAP_HEIGHT; i++){
    for (int j = 0; j < MAP_WIDTH; j++){
      putimage_alphablend(NULL, temp, 365 + 50 * j, 10 + 50 * i, 100);//����ÿ����
      if (map[i][j].bind_num){
        switch (map[i][j].bind_num){
          case 1:
            putimage_transparent(NULL, img_1, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 2:
            putimage_transparent(NULL, img_2, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 3:
            putimage_transparent(NULL, img_3, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 4:
            putimage_transparent(NULL, img_4, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 5:
            putimage_transparent(NULL, img_5, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 6:
            putimage_transparent(NULL, img_6, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 7:
            putimage_transparent(NULL, img_7, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 8:
            putimage_transparent(NULL, img_8, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
          case 9:
            putimage_transparent(NULL, img_9, 365 + 50 * j, 10 + 50 * i, EGERGB(255, 255, 255));
            break;
        }
      }
    }
  }
  delimage(temp);
}

void routine(BTN &btn, void (*f)(int, int), void (*print_screen_way)()){
  btn.set_highlight(-1);//ѡ�а�ť
  mouse_msg msg = {0};
  for (;is_run(); delay_fps(60)){
    print_screen_way();
    while (mousemsg()){
      msg = getmouse();
      if (msg.is_right()) {//�Ҽ���ȡ������
        wait_up();
        return;
      }
      else if (msg.is_left()){
        //�����겻�ڵ�ͼ��
        if (!in_map(msg.x, msg.y)){
          wait_up();
          if (!ctrl.qedit)//���ǿ��ٱ༭ģʽ
            return;
        } else {
          //����ڵ�ͼ��
          int x, y;//��������
          x = getX(msg.x);
          y = getY(msg.y);

          f(x, y);

          wait_up();
          if (!ctrl.qedit)
            return;
        }
      }
    }
  }
}
void btnf_add_track_inroutine(int x, int y){
  //����ڵ�ͼ�Ľ��������Ч
  if ((x == 0 && y == 0) || (x == 0 && y == MAP_HEIGHT - 1) || (x == MAP_WIDTH - 1 && y == 0) || (x == MAP_WIDTH - 1 && y == MAP_HEIGHT - 1));
  //�������ڷ��Ľǵ���Ϸ�߽��������
  else if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1){
    if (!map[y][x].type){//������������
      map[y][x].type = 1;
      //ֻ����Ӷ�Ӧ�����ֱ������
      if (y == 0 || y == MAP_HEIGHT - 1)
        map[y][x].rotate = 1;
    }
  }
  else if (!map[y][x].type){
    map[y][x].type = ctrl.add_track;
  }
}
void btnf_add_rotate_inroutine(int x, int y){
  //����ǵ�ͼ�߽�������
  if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1);
  //��������������
  else if (map[y][x].type == 3);
  else if (map[y][x].type != 0){
    map[y][x].child_type = 1;
    map[y][x].rotate_type = ctrl.add_rotate_type;
  }
}
void btnf_add_acc_inroutine(int x, int y){
  //����ǵ�ͼ�߽�������
  if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1);
  else if (map[y][x].type != 0){
    map[y][x].child_type = 2;
    map[y][x].speed_type = ctrl.acc_type;
  }
}
void btnf_add_boom_inroutine(int x, int y){
  //����ǵ�ͼ�߽�������
  if (x == 0 || y == 0 || x == MAP_WIDTH - 1 || y == MAP_HEIGHT - 1);
  else if (map[y][x].type != 0){
    map[y][x].child_type = 3;
  }
}
void btnf_add_station_inroutine(int x, int y){
  //�ǵ�ͼ�߽�
  if (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1)
    //���Ľ�
    if (!((x == 0 && y == 0) || (x == MAP_WIDTH - 1 && y == 0) || (x == 0 && y == MAP_HEIGHT - 1) || (x == MAP_WIDTH - 1 && y == MAP_HEIGHT - 1)))
      //������
      if (map[y][x].type)
        map[y][x].child_type = 4;
}
void btnf_get_enterxy_inroutine(int x, int y){
  if (map[y][x].child_type == 4){
    trains[ctrl.train_code - 1].enter[0] = x;
    trains[ctrl.train_code - 1].enter[1] = y;

    map[y][x].train_code = ctrl.train_code;
    map[y][x].station_type = 1;
  }
}
void btnf_get_outerxy_inroutine(int x, int y){
  if (map[y][x].child_type == 4){
    trains[ctrl.train_code - 1].outer[0] = x;
    trains[ctrl.train_code - 1].outer[1] = y;

    map[y][x].train_code = ctrl.train_code;
    map[y][x].station_type = 0;
  }
}
