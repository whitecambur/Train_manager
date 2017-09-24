#include"loading.h"
#include"creatmain.h"
#include"menu.h"
#include"diy_level.h"
#include"movingpic.h"
#include"playing.h"
#include"train.h"
int load_datas() {
	load_menu_pic();		//pic in menu.cpp
	load_movingpic();		//pic in movingpic.cpp
	load_background();		//pic in plaging.cpp
	load_pic();				//pic in train.cpp
	deal_img();				//pic in creatmain.cpp
	load_diy_menu_pic();	//pic in diy_level.cpp
	return 0;
}