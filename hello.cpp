#include"rkcg.h"

int main()
{
	initgraph(640, 480);				//初始化图形界面
	setcolor(EGERGB(0xFF, 0x0, 0x0));	//设置绘画颜色为红色
	setbkcolor(WHITE);					//设置背景颜色为白色

	setfont(14, 0, "宋体");
	//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
    //要使用特殊格式化字符请用outtextrect
    outtextxy(setCoordinateX(200), setCoordinateY(0), "X");
    outtextxy(setCoordinateX(5), setCoordinateY(200), "Y");
    // outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");
	// 画一个直角坐标系
	drawArrow(-200,0,200,0,0);
	drawScale(-180,0,180,0,0);
	drawArrow(0,-200,0,200,0);
	drawScale(0,-180,0,180,0);
	// line(setCoordinateX(-100),setCoordinateY(-50),
	// 	setCoordinateX(100),setCoordinateY(50));
	// MidPointLineX(-100,-50,100,50,0x777777);//画一条直线
	// drawCircle(100,0);//画圆,圆心在坐标原点
	// CircleBres(100,0);
	// drawCircle(100,0,50,50);//画圆,指定圆心坐标
	// drawEllipse(50,70,0,50,50);
	point pp[]={*(new point(50,10)),*(new point(20,40)),*( new point(20,80)),*(new point(70,70)),*(new point(120,110)),
		*(new point(120,50)),*(new point(70,10))};
	// scanConversionPolygon(pp,7,0x777777);
	scanConversionPolygon(pp,7,RED);
	point pp2[]={*(new point(-50,-50)),*(new point(-50,0)),*(new point(0,0)),*(new point(0,-50))};
	point pp3[]={*(new point(0,0)),*(new point(0,50)),*(new point(50,50)),*(new point(50,0))};
	scanConversionPolygon(pp2,4,0);
	scanConversionPolygon(pp3,4,0);

	//确定边界
	// MidPointLineX(-50,-50,-50,0,RED);
	// MidPointLineX(-50,0,0,0,RED);
	// MidPointLineX(0,0,0,-50,RED);
	// MidPointLineX(0,-50,-50,-50,RED);

	// FloodFill4(-25,-25,getpixel(setCoordinateX(-25),setCoordinateY(-25)),RED);
	getch();							//暂停，等待键盘按键
	closegraph();						//关闭图形界面
	return 0;
}
