
#include"rkcg.h"

using namespace rkcg;
int main(){
    //绘制画布
	drawCanvas();

	std::vector<point> points;
	points.push_back(point(50,10));
	points.push_back(point(20,40));
	points.push_back(point(20,80));
	points.push_back(point(70,70));
	points.push_back(point(120,110));
	points.push_back(point(120,50));
	points.push_back(point(70,10));
	getPolygonFromPoints(points,0);
	// 演示五种基础变换
	getPolygonFromPoints(transformationFromType(points,TRANSLATION,-50,0),0);
	getPolygonFromPoints(transformationFromType(points,PROPORTION,1.5,1.5),0);
	getPolygonFromPoints(transformationFromType(points,ROTATE,0,0,60),0);
	getPolygonFromPoints(transformationFromType(points,SYMMETRICX),0);
	getPolygonFromPoints(transformationFromType(points,SYMMETRICY),0);

	std::vector<point> pointss;
	pointss.push_back(point(50,50));
	pointss.push_back(point(100,50));
	pointss.push_back(point(100,100));
	getPolygonFromPoints(pointss,0);
	//y=50+x;
	MidPointLineX(0,50,150,200,0);
	getPolygonFromPoints(reflectionTransformationByArbitraryLine(pointss,50,1,1),0);
	MidPointLineX(20,-200,20,200,0);
	getPolygonFromPoints(reflectionTransformationByArbitraryLine(pointss,-20,1,0),0);
	MidPointLineX(-200,20,200,20,0);
	getPolygonFromPoints(reflectionTransformationByArbitraryLine(pointss,20,0,1),0);


    ege::getch();							//暂停，等待键盘按键
	ege::closegraph();						//关闭图形界面
	return 0;
}
