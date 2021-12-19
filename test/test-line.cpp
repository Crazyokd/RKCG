#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();
    
    ege::line(setCoordinateX(-100),setCoordinateY(-50),
		setCoordinateX(100),setCoordinateY(50));
	MidPointLineX(50,-50,-50,50,0x777777);//画一条直线

    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
}