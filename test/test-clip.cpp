#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	ege::ege_rect rect=ege::ege_rect();
	rect.x=rect.y=-50;
	rect.w=rect.h=100;
	drawRectangle(rect,ege::COLORS::RED);
	CohenSutherlandLineClip(-100,-100,100,100,&rect);
	CohenSutherlandLineClip(-25,-75,25,75,&rect);
	LiangBarskyLineClip(-100,-100,100,100,&rect);

	CohenSutherlandLineClip(-25,25,25,-25,&rect);
	LiangBarskyLineClip(-25,25,25,-25,&rect);
	LiangBarskyLineClip(200,-50,200,50,&rect);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}