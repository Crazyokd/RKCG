#include "graphics.h"					//包含EGE的头文件
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>

using namespace std;

// 将x坐标转换为一般坐标系x坐标
inline int setCoordinateX(int x){
	return ege::getwidth()/2+x;
}
// 将y坐标转换为一般坐标系y坐标
inline int setCoordinateY(int y){
	return ege::getheight()/2-y;
}

//对putpixel函数做一层坐标系上的封装
void putpixelRK(int x,int y,ege::color_t color){
	ege::putpixel(setCoordinateX(x),setCoordinateY(y),color);
}

//对getpixel函数做一层坐标系上的封装
ege::color_t getpixelRK(int x,int y){
	return ege::getpixel(setCoordinateX(x),setCoordinateY(y));
}
//斜率范围为[0,1]时的中点画线法
void MidPointLine0To1(int x0, int y0, int x1, int y1, ege::color_t color) {
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
void MidPointLineGt1(int x0, int y0, int x1, int y1, ege::color_t color) {
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
void MidPointLine_1To0(int x0, int y0, int x1, int y1, ege::color_t color) {
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
void MidPointLineLt_1(int x0, int y0, int x1, int y1, ege::color_t color) {
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

void MidPointLineX(int x0, int y0, int x1, int y1, ege::color_t color) {
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

void drawArrow(int x0,int y0,int x1,int y1,ege::color_t color) {
	MidPointLineX(x0,y0,x1,y1,color);
	double angle;
	if (x0 == x1)angle = ege::PI / 2;
	else angle = atan(1.0*(y1 - y0) / (x1 - x0));
	int rarrowx,rarrowy,larrowx,larrowy;
	if(x1>x0 || y1>y0){
		//左箭头
		rarrowx = x1 - 10 * cos(ege::PI / 6 + angle);
		rarrowy = y1 - 10 * sin(ege::PI / 6 + angle);
		larrowx = x1 - 10 * sin(ege::PI / 3 + angle);
		larrowy = y1 + 10 * cos(ege::PI / 3 + angle);
	}else{
		//右箭头
		rarrowx = x1 + 10 * cos(ege::PI / 6 + angle);
		rarrowy = y1 + 10 * sin(ege::PI / 6 + angle);
		larrowx = x1 + 10 * sin(ege::PI / 3 + angle);
		larrowy = y1 - 10 * cos(ege::PI / 3 + angle);
	}
	MidPointLineX(rarrowx,rarrowy,x1,y1,color);
	MidPointLineX(larrowx,larrowy,x1,y1,color);
}

void drawScale(int x0,int y0,int x1,int y1,ege::color_t color) {
	MidPointLineX(x0,y0,x1,y1,color);
	int x = x0, y = y0;
	double angle;
	if (x0 == x1)angle = ege::PI / 2;
	else angle = atan(1.0*(y1 - y0) / (x1 - x0));
	while (x <= x1&&y<=y1) {
		MidPointLineX(x - 5 * cos(ege::PI / 2 - angle), y + 5 * sin(ege::PI / 2 - angle),x,y,color);
		x = x + 50 * cos(angle);
		y = y + 50 * sin(angle);
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
void CircleBres(int  radius,ege::color_t color,int x0=0,int y0=0){
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
void drawCircle(int radius,ege::color_t color,int x0=0,int y0=0){
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
void drawEllipse(int a,int b,ege::color_t color,int x0=0,int y0=0){
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

//输出ET(辅助函数)
void printET(edge **ET,int minn,int maxx){
	for(int i=minn;i<=maxx;i++){
		if(ET[i] != NULL){
			edge *t=ET[i];
			while(t != NULL){
				printf("%x\n",t);
				printf("y=%d;ymax=%d;x=%f;deltax=%f\n",i,t->ymax,t->x,t->deltax);
				t=t->nextEdge;
			}
		}
	}
}

//删除y=ymax的边
void deleteObererPol(edge* e,int i){
	while(e->nextEdge != NULL && e->nextEdge->ymax == i){
		edge* t = e->nextEdge;
		e->nextEdge=e->nextEdge->nextEdge;
		delete t;
	}
}

//窗口最大高度
const int MAXHEIGHT=480;

//扫描转换多边形,要求按顺序给出顶点集
void scanConversionPolygon(const point pp[],int count,ege::color_t color){
	int minn=MAXHEIGHT,maxx=0;
	edge* ET[MAXHEIGHT];//适应y为负数的情况
	//初始化
	for(int i=0;i<MAXHEIGHT;i++)
		ET[i]=NULL;
	
	for(int i=0;i<count;i++){
		int t1=pp[i].y+MAXHEIGHT/2,t2=pp[(i+1)%count].y+MAXHEIGHT/2;
		if(t1==t2)continue;//忽略水平边
		int y1=t1,y2=t2,x1=pp[i].x,x2=pp[(i+1)%count].x;
		//保证y2>y1
		if(t1>t2){
			y1=t2;y2=t1;
			int t=x1;
			x1=x2;x2=t;
		}
		// printf("x1=%d;y1=%d;x2=%d;y2=%d\n",x1,y1,x2,y2);
		edge* e=new edge();
		e->ymax=y2;
		e->x=x1;
		e->deltax=1.0*(x2-x1)/(y2-y1);
		e->nextEdge=ET[y1];
		ET[y1]=e;
		minn=min(minn,y1);
		maxx=max(maxx,y2);
	}
	// printET(ET,*minn,*maxx);//打印ET

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
		}
		//删除y=ymax
		e=AEL;
		while(e != NULL && e->nextEdge != NULL){
			deleteObererPol(e,i);
			e = e->nextEdge;
		}
		e=AEL->nextEdge;
		while(e != NULL){
			// printf("%f %f %d %d %d\n",e->x+1,e->nextEdge->x,e->ymax,e->nextEdge->ymax,i);
			MidPointLineX(e->x+1,i-MAXHEIGHT/2,e->nextEdge->x,i-MAXHEIGHT/2,color);
			e->x +=e->deltax;
			e->nextEdge->x +=e->nextEdge->deltax;
			e=e->nextEdge->nextEdge;
		}

		// show process
		ege::delay(10);
	}
}



//区域填充4连通
void floodFill4(int x,int y,ege::color_t oldColor,ege::color_t newColor){
	if(getpixelRK(x,y)==oldColor){
		putpixelRK(x,y,newColor);
		floodFill4(x,y+1,oldColor,newColor);
		floodFill4(x,y-1,oldColor,newColor);
		floodFill4(x-1,y,oldColor,newColor);
		floodFill4(x+1,y,oldColor,newColor);
	}
	// ege::delay(1);
}

//调用时可以不指定oldColor
void startFloodFill4(int x,int y,ege::color_t color){
	floodFill4(x,y,getpixelRK(x,y),color);
}

typedef struct{
	int y,xLeft,xRight;
}Span;

Span constructSpan(int y,int xLeft,int xRight){
	Span span;
	span.y=y;
	span.xLeft=xLeft;
	span.xRight=xRight;
	return span;
}

void fillAdjacentScanLines(stack<Span> &ss,Span &span,int y,ege::color_t oldColor,ege::color_t newColor){
	int cursor,xleft;
	bool isConfirmLeftBoundary=false;
	//确定左边界
	cursor=span.xLeft-1;
	while(getpixelRK(cursor,y)==oldColor){
		putpixelRK(cursor,y,newColor);
		cursor--;
	}
	if(cursor!=span.xLeft-1){
		xleft=cursor+1;
		isConfirmLeftBoundary=true;
	}
	cursor=span.xLeft;
	while(cursor<span.xRight){
		bool isFill=false;
		while(getpixelRK(cursor,y)==oldColor){
			if(!isFill){
				isFill=true;
				if(!isConfirmLeftBoundary){
					xleft=cursor;
					isConfirmLeftBoundary=true;
				}	
			}
			putpixelRK(cursor,y,newColor);
			cursor++;
		}
		if(isFill){
			ss.push(constructSpan(y,xleft,cursor-1));
			isConfirmLeftBoundary=false;
			ege::delay(10);
		}
		while(getpixelRK(cursor,y)!=oldColor && cursor<span.xRight)
			cursor++;
	}
}

void scanLineFill(int x,int y,ege::color_t oldColor,ege::color_t newColor){
	int cursor;
	Span span;
	span.y=y;
	//确定左边界
	cursor=x;
	while(getpixelRK(cursor,y)==oldColor){
		putpixelRK(cursor,y,newColor);
		cursor--;
	}
	span.xLeft=cursor+1;
	//确定右边界
	cursor=x+1;
	while(getpixelRK(cursor,y)==oldColor){
		putpixelRK(cursor,y,newColor);
		cursor++;
	}
	span.xRight=cursor-1;

	stack<Span> ss;
	ss.push(span);

	while(!ss.empty()){
		span=ss.top();
		ss.pop();
		//确定上面一条扫描线
		fillAdjacentScanLines(ss,span,span.y+1,oldColor,newColor);
		//确定下面一条扫描线
		fillAdjacentScanLines(ss,span,span.y-1,oldColor,newColor);
	}
}

void startScanLineFill(int x,int y,ege::color_t color){
	scanLineFill(x,y,getpixelRK(x,y),color);
}



void drawRectangle(ege::ege_rect rect,ege::color_t color){
	MidPointLineX(rect.x,rect.y,rect.x,rect.y+rect.h,color);
	MidPointLineX(rect.x,rect.y+rect.h,rect.x+rect.w,rect.y+rect.h,color);
	MidPointLineX(rect.x+rect.w,rect.y+rect.h,rect.x+rect.w,rect.y,color);
	MidPointLineX(rect.x+rect.w,rect.y,rect.x,rect.y,color);
}
//直线段剪裁
typedef struct{
	unsigned all;
	unsigned left,right,top,bottom;
}OutCode;
void CompOutCode(float x,float y,ege::ege_rect *rect,OutCode *outCode){
	//编码方式tbrl
	outCode->all=0;
	outCode->top = y>(float)rect->y+rect->h ? 1 : 0;
	outCode->bottom = y<(float)rect->y ? 1 : 0;
	outCode->right = x>(float)rect->x+rect->w ? 1 : 0;
	outCode->left = x<(float)rect->x ? 1 : 0;

	outCode->all += outCode->top;
	outCode->all <<= 1;outCode->all += outCode->bottom;
	outCode->all <<= 1;outCode->all += outCode->right;
	outCode->all <<= 1;outCode->all += outCode->left;
}

//CohenSutherland算法实现直线段剪裁
void CohenSutherlandLineClip(float x0,float y0,float x1,float y1,ege::ege_rect *rect,ege::color_t color=0){
	boolean accept,done;
	OutCode outCode0,outCode1;
	OutCode *outCodeOut;
	float x,y;
	accept=false;
	done=false;
	CompOutCode(x0,y0,rect,&outCode0);
	CompOutCode(x1,y1,rect,&outCode1);
	do{
		//完全可见
		if(outCode0.all == 0 && outCode1.all == 0){
			accept=true;
			done=true;
		}else if(outCode0.all & outCode1.all){//完全不可见
			done=true;
		}else{
			if(outCode0.all)outCodeOut=&outCode0;
			else outCodeOut=&outCode1;
			if(outCodeOut->left){
				y=y0+(rect->x-x0)*(y1-y0)/(x1-x0);
				x=(float)rect->x;
			}else if(outCodeOut->top){
				x=x0+(x1-x0)*(rect->y+rect->h-y0)/(y1-y0);
				y=(float)rect->y+rect->h;
			}else if(outCodeOut->right){
				y=y0+(y1-y0)*(rect->x+rect->w-x0)/(x1-x0);
				x=(float)rect->x+rect->w;
			}else if(outCodeOut->bottom){
				x=x0+(x1-x0)*(rect->y-y0)/(y1-y0);
				y=(float)rect->y;
			}
			if(outCodeOut==&outCode0){
				x0=x;
				y0=y;
				CompOutCode(x0,y0,rect,&outCode0);
			}else{
				x1=x;
				y1=y;
				CompOutCode(x1,y1,rect,&outCode1);
			}
		}
	}while(!done);
	if(accept)MidPointLineX((int)x0,(int)y0,(int)x1,(int)y1,color);
}

//当线段完全不可见时，返回false
boolean ClipT(float q,float d,float *t0,float *t1){
	float r;
	if(q<0){
		r=d/q;
		if(r>*t1)return false;
		else if(r>*t0){
			*t0=r;
			return true;
		}
	}else if(q>0){
		r=d/q;
		if(r<*t0){
			return false;
		}else if(r<*t1){
			*t1=r;
			return true;
		}

	}else if(d<0){
		return false;
	}
	return true;
}

void LiangBarskyLineClip(float x0,float y0,float x1,float y1,ege::ege_rect *rect){
	float deltax,deltay,t0,t1;
	t0=0,t1=1;
	deltax=x1-x0;
	if(ClipT(-deltax,x0-rect->x,&t0,&t1)){
		if(ClipT(deltax,rect->x+rect->w-x0,&t0,&t1)){
			deltay=y1-y0;
			if(ClipT(-deltay,y0-rect->y,&t0,&t1)){
				if(ClipT(deltay,rect->y+rect->h-y0,&t0,&t1)){
					MidPointLineX((int)(x0+t0*deltax),(int)(y0+t0*deltay),
					(int)(x0+t1*deltax),(int)(y0+t1*deltay),0);
					return;
				}
			}
		}
	}
	std::cout<<"完全不可见";
}
