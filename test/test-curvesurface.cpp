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
	pp1.push_back(point(0,100));
	for(int i=1;i<4;i++)
		pp1.push_back(point(pp1[i-1].x-30*DEVIATION,pp1[i-1].y-30*DEVIATION));

	ppp2.push_back(point(40,60));
	for(int i=1;i<4;i++)
		ppp2.push_back(point(ppp2[i-1].x-30*DEVIATION,ppp2[i-1].y-30*DEVIATION));

	ppp3.push_back(point(100,120));
	for(int i=1;i<4;i++)
		ppp3.push_back(point(ppp3[i-1].x-30*DEVIATION,ppp3[i-1].y-30*DEVIATION));

	pp4.push_back(point(120,80));
	for(int i=1;i<4;i++)
		pp4.push_back(point(pp4[i-1].x-30*DEVIATION,pp4[i-1].y-30*DEVIATION));

	ppp.push_back(pp1);
	ppp.push_back(ppp2);
	ppp.push_back(ppp3);
	ppp.push_back(pp4);

	connectPoints(drawBezierCurveSurface(ppp),0);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}
