#pragma once
#include"draw.h"
class button {
public:
	void creat(int x,int y,int w,int h,PIMAGE pimg);
	int action(mouse_msg the_mouse);
	void del_btn();
private:
	int x, y;
	int w, h;
	PIMAGE pimg;
};