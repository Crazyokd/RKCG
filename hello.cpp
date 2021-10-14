#include <graphics.h>					//包含EGE的头文件
#include<iostream>
#include<cmath>
#include<algorithm>

using namespace std;

// 将x坐标转换为一般坐标系x坐标
int setCoordinateX(int x){
	return getwidth()/2+x;
}
// 将y坐标转换为一般坐标系y坐标
int setCoordinateY(int y){
	return getheight()/2-y;
}

//对putpixel函数做一层坐标系上的封装
void putpixelRK(int x,int y,color_t color){
	putpixel(setCoordinateX(x),setCoordinateY(y),color);
}
//斜率范围为[0,1]时的中点画线法
void MidPointLine0To1(int x0, int y0, int x1, int y1, color_t color) {
	int dx = x1 - x0, dy = y1 - y0;
	int d = dx - 2 * dy; //初始化判别式d
	int E = -2 * dy, NE = -2 * (dy - dx);
	int x = x0, y = y0;
	while (x <= x1) {
		putpixelRK(x,y,color);
		if (d > 0)d += E;
		else {
			d += NE;
			y++;
		}
		x++;
	}  
}

//斜率范围为[1,]时的中点画线法
void MidPointLineGt1(int x0, int y0, int x1, int y1, color_t color) {
	int dx = x1 - x0, dy = y1 - y0;
	int d = 2*dx - dy; //初始化判别式d
	int E = 2 * dx, NE = 2 * (dx - dy);
	int x = x0, y = y0;
	while (y <= y1) {
		putpixelRK(x,y,color);
		if (d < 0)d += E;
		else {
			d += NE;
			x++;
		}
		y++;
	}
}

//斜率范围为[-1,0]时的中点画线法
void MidPointLine_1To0(int x0, int y0, int x1, int y1, color_t color) {
	int dx = x1 - x0, dy = y1 - y0;
	int d = -dx - 2*dy; //初始化判别式d
	int E = -2 * dy, NE = -2 * (dx + dy);
	int x = x0, y = y0;
	while (x <= x1) {
		putpixelRK(x,y,color);
		if (d < 0)d += E;
		else {
			d += NE;
			y--;
		}
		x++;
	}
}

//斜率范围为[,-1]时的中点画线法
void MidPointLineLt_1(int x0, int y0, int x1, int y1, color_t color) {
	int dx = x1 - x0, dy = y1 - y0;
	int d = -2*dx -  dy; //初始化判别式d
	int E = -2 * dy-2*dx, NE = -2 * dx;
	int x = x0, y = y0;
	while (x <= x1) {
		putpixelRK(x,y,color);
		if (d < 0) {
			d += E;
			x++;
		}
		else d += NE;
		y--;
	}
}

void MidPointLineX(int x0, int y0, int x1, int y1, color_t color) {
	int dx = x1 - x0, dy = y1 - y0;
	//斜率为[0,1]的情况
	if (!dy||(dy*dx > 0 && abs(dy) <= abs(dx))) {
		MidPointLine0To1(min(x0,x1), min(y0,y1), max(x0,x1), max(y0,y1), color);
	}
	//斜率为[1,]的情况
	if (!dx||(dy*dx > 0 && abs(dy) > abs(dx))) {
		MidPointLineGt1(min(x0,x1), min(y0,y1), max(x0,x1), max(y0,y1), color);
	}
	//斜率为[-1,0]的情况
	if (dy*dx < 0 && abs(dy) <= abs(dx)) {
		MidPointLine_1To0(min(x0,x1), max(y0,y1), max(x0,x1), min(y0,y1), color);
	}
	//斜率<-1的情况
	if (dy*dx<0 && abs(dy)>abs(dx)) {
		MidPointLineLt_1(min(x0,x1), max(y0,y1), max(x0,x1), min(y0,y1), color);
	}
}

void drawArrow(int x0,int y0,int x1,int y1,color_t color) {
	MidPointLineX(x0,y0,x1,y1,color);
	double angle;
	if (x0 == x1)angle = PI / 2;
	else angle = atan(1.0*(y1 - y0) / (x1 - x0));
	int rarrowx,rarrowy,larrowx,larrowy;
	if(x1>x0 || y1>y0){
		//左箭头
		rarrowx = x1 - 10 * cos(PI / 6 + angle);
		rarrowy = y1 - 10 * sin(PI / 6 + angle);
		larrowx = x1 - 10 * sin(PI / 3 + angle);
		larrowy = y1 + 10 * cos(PI / 3 + angle);
	}else{
		//右箭头
		rarrowx = x1 + 10 * cos(PI / 6 + angle);
		rarrowy = y1 + 10 * sin(PI / 6 + angle);
		larrowx = x1 + 10 * sin(PI / 3 + angle);
		larrowy = y1 - 10 * cos(PI / 3 + angle);
	}
	MidPointLineX(rarrowx,rarrowy,x1,y1,color);
	MidPointLineX(larrowx,larrowy,x1,y1,color);
}

void drawScale(int x0,int y0,int x1,int y1,color_t color) {
	MidPointLineX(x0,y0,x1,y1,color);
	int x = x0, y = y0;
	double angle;
	if (x0 == x1)angle = PI / 2;
	else angle = atan(1.0*(y1 - y0) / (x1 - x0));
	while (x <= x1&&y<=y1) {
		MidPointLineX(x - 5 * cos(PI / 2 - angle), y + 5 * sin(PI / 2 - angle),x,y,color);
		x = x + 10 * cos(angle);
		y = y + 10 * sin(angle);
	}
}

//绘制圆上对称的八个点
const int CIRCLE=8;
const int ELLIPSE=4;

//绘制椭圆上对称的四个点
void drawSymmetricPoints(int x,int y,int color,int type,int x0=0,int y0=0){
	int points[][2]={{x,y},{-x,y},{x,-y},{-x,-y},
	{y,x},{-y,x},{y,-x},{-y,-x}};
	for(int i=0;i<type;i++){
		putpixelRK(points[i][0]+x0,points[i][1]+y0,color);
	}
}

//中点算法绘制原形
void drawCircle(int radius,color_t color,int x0=0,int y0=0){
	int x=0,y=radius,d=5-4*radius;
	int deltaE=12,deltaSE=20-8*radius;
	while(y>=x){
		drawSymmetricPoints(x,y,color,CIRCLE,x0,y0);
		if(d<=0){
			d+=deltaE;
			deltaSE+=8;
		}else{
			d+=deltaSE;
			deltaSE+=16;
			y--;
		}
		deltaE+=8;//即使没有使用也要同步更新
		x++;	
	}
}

//中点算法绘制椭圆
void drawEllipse(int a,int b,color_t color,int x0=0,int y0=0){
	int x,y,d;
	int square_a=a*a,square_b=b*b;
	//计算分界点（斜率为1处）
	int xB=0.5+square_a/sqrt(square_a+square_b);
	int yB=0.5+square_b/sqrt(square_a+square_b);

	//生成第一象限内的上半部分椭圆弧
	x=0;y=b;
	d=4*(square_b-square_a*b)+square_a;//初始化
	while(x<=xB){
		drawSymmetricPoints(x,y,color,ELLIPSE,x0,y0);
		int t=4*square_b*(2*x+3);
		if(d<=0)d+=t;
		else{
			d+=t-8*square_a*(y-1);
			y--;
		}
		x++;
	}

	//生成第一象限内的下半部分椭圆弧
	x=a;y=0;
	d=4*(square_a-a*square_b)+square_b;//初始化
	while(y<yB){
		drawSymmetricPoints(x,y,color,ELLIPSE,x0,y0);
		int t=4*square_a*(2*y+3);
		if(d<=0)d+=t;
		else{
			d+=t-8*square_b*(x-1);
			x--;
		}
		y++;
	}
}

int main()
{
	initgraph(640, 480);				//初始化图形界面
	setcolor(EGERGB(0xFF, 0x0, 0x0));	//设置绘画颜色为红色
	setbkcolor(WHITE);					//设置背景颜色为白色
	// 画一个直角坐标系
	drawArrow(-200,0,200,0,0);
	drawScale(-180,0,180,0,0);
	drawArrow(0,-200,0,200,0);
	drawScale(0,-180,0,180,0);
	// line(setCoordinateX(-100),setCoordinateY(-50),
	// 	setCoordinateX(100),setCoordinateY(50));
	MidPointLineX(-100,-50,100,50,0x777777);//画一条直线
	// drawCircle(100,0);//画圆,圆心在坐标原点
	drawCircle(100,0,50,50);//画圆,指定圆心坐标
	drawEllipse(50,70,0,50,50);
	getch();							//暂停，等待键盘按键
	closegraph();						//关闭图形界面
	return 0;
}
