#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	// 确定边界
	MidPointLineX(-50,-50,-50,0,ege::RED);
	MidPointLineX(-50,0,0,0,ege::RED);
	MidPointLineX(0,0,0,-50,ege::RED);
	MidPointLineX(0,-50,-50,-50,ege::RED);

	startFloodFill4(-15,-25,ege::GREEN);
	startScanLineFill(65,25,ege::BLUE);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}