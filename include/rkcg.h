#include "graphics.h"					//包含EGE的头文件
#include <iostream>
#include <cmath>
#include <algorithm>
#include <stack>
#include <vector>

namespace rkcg{
	#define DEVIATION 0.707107		// cos(PI/4)

	// 将x坐标转换为一般坐标系x坐标
	inline int setCoordinateX(int x){
		return ege::getwidth()/2+x;
	}
	// 将y坐标转换为一般坐标系y坐标
	inline int setCoordinateY(int y){
		return ege::getheight()/2-y;
	}

	//对putpixel函数做一层坐标系上的封装
	void putpixelRK(int x,int y,ege::color_t color,int z=0){
		ege::putpixel(setCoordinateX(x-z*DEVIATION),setCoordinateY(y-z*DEVIATION),color);
	}

	//对getpixel函数做一层坐标系上的封装
	ege::color_t getpixelRK(int x,int y,int z=0){
		return ege::getpixel(setCoordinateX(x-z*DEVIATION),setCoordinateY(y-z*DEVIATION));
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
			MidPointLine0To1(std::min(x0,x1), std::min(y0,y1), std::max(x0,x1), std::max(y0,y1), color);
		}
		//斜率为[1,]的情况
		if (!dx||(dy*dx > 0 && abs(dy) > abs(dx))) {
			MidPointLineGt1(std::min(x0,x1), std::min(y0,y1), std::max(x0,x1), std::max(y0,y1), color);
		}
		//斜率为[-1,0]的情况
		if (dy*dx < 0 && abs(dy) <= abs(dx)) {
			MidPointLine_1To0(std::min(x0,x1), std::max(y0,y1), std::max(x0,x1), std::min(y0,y1), color);
		}
		//斜率<-1的情况
		if (dy*dx<0 && abs(dy)>abs(dx)) {
			MidPointLineLt_1(std::min(x0,x1), std::max(y0,y1), std::max(x0,x1), std::min(y0,y1), color);
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



	//绘制画布
	void drawCanvas(){
		ege::initgraph(640, 480);				//初始化图形界面
		ege::setcolor(EGERGB(0xFF, 0x0, 0x0));	//设置绘画颜色为红色
		ege::setbkcolor(ege::WHITE);					//设置背景颜色为白色

		ege::setfont(14, 0, "宋体");
		//写文字，注意：outtextxy不支持\t \n这类格式化用的特殊字符，这类字符会被忽略
		//要使用特殊格式化字符请用outtextrect
		ege::outtextxy(setCoordinateX(200), setCoordinateY(0), "X");
		ege::outtextxy(setCoordinateX(5), setCoordinateY(200), "Y");
		ege::outtextxy(setCoordinateX(-150),setCoordinateY(-150),"Z");
		// outtextrect(100, 120, 200, 100, "\tHello EGE Graphics\nHere is the next line.");
		// 画一个直角坐标系
		drawArrow(-200,0,200,0,0);
		drawScale(-180,0,180,0,0);
		drawArrow(0,-200,0,200,0);
		drawScale(0,-180,0,180,0);
		//画Z轴
		drawArrow(150,150,-150,-150,0);
	}



	const int CIRCLE=8;
	const int ELLIPSE=4;

	//绘制对称点
	void drawSymmetricPoints(int x,int y,int color,int type,int x0=0,int y0=0,int z=0){
		int points[][2]={{x,y},{-x,y},{x,-y},{-x,-y},
		{y,x},{-y,x},{y,-x},{-y,-x}};
		for(int i=0;i<type;i++){
			putpixelRK(points[i][0]+x0,points[i][1]+y0,color,z);
		}
	}

	//BresenHam算法绘制圆形
	void CircleBres(int  radius,ege::color_t color,int x0=0,int y0=0,int z=0){
		int x=0,y=radius,p=3-2*radius;
		while (x<=y){
			drawSymmetricPoints(x,y,color,CIRCLE,x0,y0,z);
			x++;
			if (p<0)p+=(4*x+6);
			else{
				p+=(4*(x-y)+10);
				y--;
			}
		}
	}

	//中点算法绘制圆形
	void drawCircle(int radius,ege::color_t color,int x0=0,int y0=0,int z=0){
		int x=0,y=radius,d=5-4*radius;
		int deltaE=12,deltaSE=20-8*radius;
		while(y>=x){
			drawSymmetricPoints(x,y,color,CIRCLE,x0,y0,z);
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
	void drawEllipse(int a,int b,ege::color_t color,int x0=0,int y0=0,int z=0){
		int x,y,d;
		int square_a=a*a,square_b=b*b;
		//计算分界点（斜率为1处）
		int xB=0.5+square_a/sqrt(square_a+square_b);
		int yB=0.5+square_b/sqrt(square_a+square_b);

		//生成第一象限内的上半部分椭圆弧
		x=0;y=b;
		d=4*(square_b-square_a*b)+square_a;//初始化
		while(x<=xB){
			drawSymmetricPoints(x,y,color,ELLIPSE,x0,y0,z);
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
			drawSymmetricPoints(x,y,color,ELLIPSE,x0,y0,z);
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
		int x,y,z;
		point(int xx,int yy):x(xx),y(yy),z(0){}
		point(int x,int y,int z):point(x,y){
			this->z=z;
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
			minn=std::min(minn,y1);
			maxx=std::max(maxx,y2);
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

	void fillAdjacentScanLines(std::stack<Span> &ss,Span &span,int y,ege::color_t oldColor,ege::color_t newColor){
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

		std::stack<Span> ss;
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


	//
	//图形变换
	//
	//按顺序连接各点，但首尾不连接
	void connectPoints(std::vector<point> points,ege::color_t color){
		if(points.empty())return;
		point first_point = points.back();
		point pre_point = first_point;
		points.pop_back();

		while(!points.empty()){
			point cur_point = points.back();
			MidPointLineX(pre_point.x,pre_point.y,cur_point.x,cur_point.y,color);
			pre_point = cur_point;
			points.pop_back();
		}
	}

	//通过点集画出一个多边形
	void getPolygonFromPoints(std::vector<point> points,ege::color_t color){
		MidPointLineX(points[0].x,points[0].y,points[points.size()-1].x,points[points.size()-1].y,color);
		connectPoints(points,color);
	}

	#define TRANSLATION 0	//平移
	#define PROPORTION 1	//比例
	#define ROTATE 2		//旋转
	#define SYMMETRICX 3		//关于X轴对称
	#define SYMMETRICY 4		//关于Y轴对称

	//矩阵乘法
	point matrixMultiplication(point pit,float tx,float ty,int type,int angle){
		//定义通用矩阵
		float transformation[3][3]={
			{1,0,0},
			{0,1,0},
			{0,0,1}
		};
		float point_of_transformation[3]={
			0,0,1
		};
		point_of_transformation[0]=pit.x,point_of_transformation[1]=pit.y;
		float res[3]={
			0,0,0
		};
		if(type == TRANSLATION){
			transformation[2][0] = tx;
			transformation[2][1] = ty;
		}else if(type == PROPORTION){
			transformation[0][0] = tx;
			transformation[1][1] = ty;
		}else if(type == ROTATE){
			double radian = angle*ege::PI / 180;
			transformation[0][0] = transformation[1][1] = cos(radian);
			transformation[0][1] = sin(radian);
			transformation[1][0] = -transformation[0][1];
		}else if(type == SYMMETRICX){
			transformation[1][1] = -1;
		}else if(type == SYMMETRICY){
			transformation[0][0] = -1;
		}else{
			std::cout << "指定的类型无效" << std::endl;
		}
		//matrixMultiplication
		for(int i=0;i<3;i++){
			for(int j=0;j<3;j++){
				res[i]+=point_of_transformation[j]*transformation[j][i];
			}
		}
		return point(res[0],res[1]);
	}
	//依据type确定变换类型。
	//【当指定type=ROTATE时，tx、ty失效】
	std::vector<point> transformationFromType(std::vector<point> points,int type,float tx=0,float ty=0,int angle=0){
		std::vector<point> pre_points;
		while(!points.empty()){
			pre_points.push_back(matrixMultiplication(points.back(),tx,ty,type,angle));
			points.pop_back();
		}
		// getPolygonFromPoints(pre_points,0);
		return pre_points;
	}

	//关于任意的反射轴 cy=a+bx 进行反射变换
	std::vector<point> reflectionTransformationByArbitraryLine(std::vector<point> points,float a,float b,float c){
		int angle = atan(b)*180 / ege::PI >= 0 ? atan(b)*180 / ege::PI : 180+atan(b)*180 / ege::PI;
		std::vector<point> pre_points;
		//使反射轴与坐标轴重合
		if(c == 0){	//与y轴平行
			pre_points = transformationFromType(transformationFromType(points,TRANSLATION,a/b,0),SYMMETRICY);
			return transformationFromType(pre_points,TRANSLATION,-a/b,0);
		}else{	//普通情况
			//平移——》旋转——》对称
			pre_points = transformationFromType(transformationFromType(transformationFromType(points,TRANSLATION,0,-a),ROTATE,0,0,-angle),SYMMETRICX);
			//旋转——》平移
			return transformationFromType(transformationFromType(pre_points,ROTATE,0,0,angle),TRANSLATION,0,a);
		}
	}

	int fac(int n){
		if (n == 1 || n == 0)
			return 1;
		else
			return n * fac(n - 1);
	}

	//根据给定的基准点点集得到比塞尔曲线点集
	std::vector<point> getPointOfBezierCurve(std::vector<point> &datum_points,int num = 100){
		std::vector<point> res_points;
		double a, b;
		double temp, temp1, temp2, bi;
		int len=datum_points.size()-1;
		for (double t = 0.0; t <= 1; t += 1.0 / num){
			a = 0.0;
			b = 0.0;
			for (int i = 0; i <= len; ++i){
				temp = 1.0*fac(len) / fac(i) / fac(len - i);
				temp1 = pow(t, i);
				temp2 = pow(1 - t, len - i);
				bi = temp * temp1 * temp2;
				a += bi * datum_points[i].x;
				b += bi * datum_points[i].y;
			}
			// printf("x=%lf;y=%lf\n",a,b);
			res_points.push_back({(int)a,(int)b});
		}
		return res_points;
	}


	// 使用Bezier算法绘制曲面
	std::vector<point> drawBezierCurveSurface(std::vector<std::vector<point>> datum_points,int num = 100){
		//将三维坐标转换为二维坐标
		for(int i=0;i<datum_points.size();i++){
			for(int j=0;j<datum_points[i].size();j++){
				datum_points[i][j].x -= datum_points[i][j].z * DEVIATION;
				datum_points[i][j].y -= datum_points[i][j].z * DEVIATION;
			}
		}
		std::vector<point> res_points;
		double a, b;
		double temp, temp1, temp2, bi1, bi2;
		int len1=datum_points.size()-1;
		int len2=datum_points[0].size()-1;
		for (double u = 0.0; u <= 1; u += 1.0 / num){
			for(double v = 0.0; v <= 1;v += 1.0 / num){
				a = 0.0;
				b = 0.0;
				for(int i = 0; i<= len1 ; i++){
					temp = 1.0*fac(len1) / fac(i) / fac(len1 - i);
					temp1 = pow(u, i);
					temp2 = pow(1 - u, len1 - i);
					bi1 = temp * temp1 * temp2;
					for(int j = 0;j <= len2; j++){
						temp = 1.0*fac(len2) / fac(j) / fac(len2 - j);
						temp1 = pow(v, j);
						temp2 = pow(1 - v, len2 - j);
						bi2 = temp * temp1 * temp2;
						a += bi1 * bi2 * datum_points[i][j].x;
						b += bi1 * bi2 * datum_points[i][j].y;
					}
				}
				// printf("x=%lf;y=%lf\n",a,b);
				res_points.push_back({(int)a,(int)b});
			}
		}
		return res_points;
	}
}