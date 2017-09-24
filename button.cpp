#include"button.h"
void button::creat(int x, int y, int w, int h, PIMAGE pimg) {
	this->x = x;
	this->y = y;
	this->w = w;
	this->h = h;
	this->pimg = pimg;
}
int button::action(mouse_msg the_mouse) {
	int flag = 0;
	PIMAGE p = newimage(this->w, this->h);
	if (the_mouse.x > this->x&&the_mouse.x<this->x + this->w&&the_mouse.y>this->y&&the_mouse.y < this->y + this->h) {
		if (the_mouse.is_up() == true) {		//释放
			if (this->pimg != NULL) {
				putimage_transparent(NULL, this->pimg, this->x, this->y, BLACK, 0, 0, this->w, this->h);
			}
			flag = 1;
		}
		else if(the_mouse.is_down() == true){	//点击
			if (this->pimg != NULL) {
				putimage_transparent(NULL, this->pimg, this->x, this->y, BLACK, 0, 2 * this->h, this->w, this->h);
			}
			else {
				putimage_alphablend(NULL, p, this->x, this->y, 150);
			}
		}
		else {									//鼠标经过
			if (this->pimg != NULL) {
				putimage_transparent(NULL, this->pimg, this->x, this->y, BLACK, 0, this->h, this->w, this->h);
			}
			else {
				setbkcolor(WHITE, p);
				putimage_alphablend(NULL, p, this->x, this->y, 150);
			}
		}
	}
	else {
		if (this->pimg != NULL) {
			putimage_transparent(NULL, this->pimg, this->x, this->y, BLACK, 0, 0, this->w, this->h);
		}
	}
	delimage(p);
	p = NULL;
	return flag;
}
void button::del_btn() {
	if (this->pimg != NULL) {
		this->pimg = NULL;
	}
}