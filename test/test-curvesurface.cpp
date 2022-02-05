#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	std::vector<std::vector<point>> ppp;
	std::vector<point> pp1;
	std::vector<point> ppp2;
	std::vector<point> ppp3;
	std::vector<point> pp4;
	std::vector<point> pp5;
	pp1.push_back(point(-120,0,0));
	for(int i=1;i<5;i++)
		pp1.push_back(point(pp1[i-1].x,pp1[i-1].y,30*i));

	ppp2.push_back(point(0,150,0));
	for(int i=1;i<5;i++)
		ppp2.push_back(point(ppp2[i-1].x,ppp2[i-1].y,30*i));

	ppp3.push_back(point(250,0,0));
	for(int i=1;i<5;i++)
		ppp3.push_back(point(ppp3[i-1].x,ppp3[i-1].y,30*i));

	pp4.push_back(point(0,-110,0));
	for(int i=1;i<5;i++)
		pp4.push_back(point(pp4[i-1].x,pp4[i-1].y,30*i));
	
	pp5.push_back(point(100,-150,0));
	for(int i=1;i<5;i++)
		pp5.push_back(point(pp5[i-1].x,pp5[i-1].y,30*i));


	ppp.push_back(pp1);
	ppp.push_back(ppp2);
	ppp.push_back(ppp3);
	ppp.push_back(pp4);
	ppp.push_back(pp5);

	connectPoints(drawBezierCurveSurface(ppp,1000),0);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}
