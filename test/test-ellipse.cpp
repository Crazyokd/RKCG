#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	
    drawEllipse(50,70,0,50,50);

    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}