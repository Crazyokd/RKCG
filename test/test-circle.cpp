#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	
	// CircleBres(100,0);
	drawCircle(100,0);//画圆,圆心在坐标原点
	drawCircle(100,0,50,50);//画圆,指定圆心坐标

    drawCircle(100,0,0,0,100);//绘制三维上的圆
    drawCircle(100,0,0,0,-100);//绘制三维上的圆

    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}