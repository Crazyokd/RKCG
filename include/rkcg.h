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

const int CIRCLE=8;
const int ELLIPSE=4;

//绘制对称点
void drawSymmetricPoints(int x,int y,int color,int type,int x0=0,int y0=0){
	int points[][2]={{x,y},{-x,y},{x,-y},{-x,-y},
	{y,x},{-y,x},{y,-x},{-y,-x}};
	for(int i=0;i<type;i++){
		putpixelRK(points[i][0]+x0,points[i][1]+y0,color);
	}
}

//BresenHam算法绘制圆形
void CircleBres(int  radius,color_t color,int x0=0,int y0=0){
	int x=0,y=radius,p=3-2*radius;
 	while (x<=y){
		drawSymmetricPoints(x,y,color,CIRCLE,x0,y0);
		x++;
		if (p<0)p+=(4*x+6);
		else{
			p+=(4*(x-y)+10);
			y--;
		}
    }
}

//中点算法绘制圆形
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

struct point{
	int x,y;
	point(int x,int y){
		this->x=x;
		this->y=y;
	}
};

struct edge{
	int ymax;
	float x,deltax;
	struct edge *nextEdge;
	edge(){
		this->nextEdge=NULL;
	}
	edge(int ymax){
		this->ymax=ymax;
		this->x=this->deltax=0.0;
		this->nextEdge=NULL;
	}
};

//窗口最大高度
const int MAXHEIGHT=480;

//将点作预处理
edge** buildET(point pp[],int count,int *minn,int *maxx){
	edge* ET[MAXHEIGHT];
	//初始化
	for(int i=0;i<MAXHEIGHT;i++)
		ET[i]=NULL;
	
	for(int i=0;i<count;i++){
		int t1=pp[i].y,t2=pp[(i+1)%count].y;
		if(t1==t2)continue;//忽略水平边
		int y1=t1,y2=t2,x1=pp[i].x,x2=pp[(i+1)%count].x;
		//保证y2>y1
		if(t1>t2){
			y1=t2;y2=t1;
			int t=x1;
			x1=x2;x2=t;
		}
		edge* e=new edge();
		e->ymax=y2;
		e->x=x1;
		e->deltax=1.0*(x2-x1)/(y2-y1);
		e->nextEdge=ET[y1];
		ET[y1]=e;
		*minn=min(*minn,y1);
		*maxx=max(*maxx,y2);
	}
	edge** et=ET;
	return et;
}

void deleteObererPol(edge* e,int i){
	while(e->nextEdge != NULL && e->nextEdge->ymax == i){
		edge* t = e->nextEdge;
		e->nextEdge=e->nextEdge->nextEdge;
		delete t;
	}
}

void convertFromPointToEdge(point pp[],int count,color_t color){
	int minn=MAXHEIGHT,maxx=0;
	edge** ET=buildET(pp,count,&minn,&maxx);
	// printf("%d %d\n",minn,maxx);
	edge* AEL=new edge(0);//作为根节点
	for(int i=minn;i<=maxx;i++){
		edge *e=ET[i];
		//插入链表并排序
		while(e!=NULL){
			edge* tmp=AEL;
			while(tmp->nextEdge!=NULL){
				if(tmp->nextEdge->x > e->x || tmp->nextEdge->x == e->x && tmp->nextEdge->deltax > e->deltax)
					break;
				tmp=tmp->nextEdge;
			}
			edge *t = e->nextEdge;
			e->nextEdge = tmp->nextEdge;
			tmp->nextEdge = e;
			e=t;
			printf("添加了一条边,x=%d\n",tmp->nextEdge->x);
		}
		e=AEL;
		while(e != NULL && e->nextEdge != NULL){
			deleteObererPol(e,i);
			e = e->nextEdge;
		}
		e=AEL->nextEdge;
		while(e != NULL){
			// printf("%f %f %d %d %d\n",e->x,e->nextEdge->x,e->ymax,e->nextEdge->ymax,i);
			MidPointLineX(e->x,i,e->nextEdge->x,i,0x777777);
			e->x +=e->deltax;
			e->nextEdge->x +=e->nextEdge->deltax;
			e=e->nextEdge->nextEdge;
		}
	}
}
