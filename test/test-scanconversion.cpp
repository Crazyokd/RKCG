#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	
	point pp2[]={*(new point(-50,-50)),*(new point(-50,0)),*(new point(0,0)),*(new point(0,-50))};
	point pp3[]={point(0,0),point(0,50),point(50,50),point(50,0)};
	scanConversionPolygon(pp2,4,ege::GREEN);
	scanConversionPolygon(pp3,4,0);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}