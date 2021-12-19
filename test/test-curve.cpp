#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	std::vector<point> datum_points;
	datum_points.push_back({140, 25});
	datum_points.push_back({150, 100});
	datum_points.push_back({175, 125});
	datum_points.push_back({200, 25});
	
	connectPoints(getPointOfBezierCurve(datum_points),0);

	std::vector<point> datum_points2;
	datum_points2.push_back({-140, -25});
	datum_points2.push_back({-150, -100});
	datum_points2.push_back({-175, -125});
	datum_points2.push_back({-200, -25});
	datum_points2.push_back({-210,0});
	connectPoints(getPointOfBezierCurve(datum_points2),ege::RED);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}
